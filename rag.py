from langchain.document_loaders import TextLoader

loader = TextLoader("big.txt")
data = loader.load()
text = data[0].page_content
len(text)

import numpy as np
from sklearn.metrics.pairwise import cosine_similarity
from sentence_transformers import SentenceTransformer

class DynamicChunker:
    def __init__(self, embedding_model='paraphrase-MiniLM-L6-v2', window_size=100):
        self.model = SentenceTransformer(embedding_model)
        self.window_size = window_size
        self.parent_embeddings = []
        self.groups = []

    def embed_sentence(self, sentence):
        return self.model.encode(sentence)

    def add_embedding_to_group(self, sentence):
        embedding = self.embed_sentence(sentence)

        if not self.parent_embeddings:
            # First sentence, create a new group
            self.parent_embeddings.append(embedding)
            self.groups.append([sentence])
        else:
            similarities = cosine_similarity([embedding], self.parent_embeddings).flatten()
            #print(f"Similarities: {similarities}")
            best_group_index = np.argmax(similarities)
            max_similarity = similarities[best_group_index]

            threshold = 0.5  # Adjust as needed

            if max_similarity > threshold:
                # Sentence is similar to an existing group
                self.groups[best_group_index].append(sentence)
                group_embeddings = [self.embed_sentence(s) for s in self.groups[best_group_index]]
                self.parent_embeddings[best_group_index] = np.mean(group_embeddings, axis=0)
            else:
                # Sentence is not similar to existing groups, create a new group
                self.parent_embeddings.append(embedding)
                self.groups.append([sentence])

        # if len(self.parent_embeddings) > self.window_size:
        #     self.parent_embeddings.pop(0)
            #self.groups.pop(0)

    def get_groups(self):
        return self.groups


# Split text into sentences
sentences = [sentence.strip() for sentence in text.split('. ') if sentence.strip()]

chunker = DynamicChunker(window_size=10)

for sentence in sentences:
    chunker.add_embedding_to_group(sentence)

for i, group in enumerate(chunker.get_groups()):
    print(f"Group {i + 1}: {group}")





import faiss
groups = chunker.get_groups()

# Initialize FAISS index (128 is the dimension size of SentenceTransformer embeddings)
dimension = 384  # % Changed the dimension size to match the embedding size of the SentenceTransformer model
faiss_index = faiss.IndexFlatL2(dimension)  # % Added FAISS index initialization

# Convert chunks to embeddings and add to FAISS
for i, group in enumerate(groups):
    # Combine all sentences in the group to form a chunk
    chunk_text = ' '.join(group)  # % Combine sentences in each group into a chunk
    
    # Generate embedding for the entire chunk
    chunk_embedding = chunker.embed_sentence(chunk_text)  # % Generate embedding for the chunk
    
    # Add the embedding to the FAISS index
    faiss_index.add(np.array([chunk_embedding]))  # % Add chunk embedding to FAISS index
    
    print(f"Added chunk {i + 1} to FAISS index.")  # % Marked the addition of chunks to FAISS

# Check the total number of embeddings stored in FAISS
print(f"Total chunks in FAISS: {faiss_index.ntotal}")



def search_faiss_index(query, chunker, faiss_index, groups, top_k=5):
    # Step 1: Embed the query
    query_embedding = chunker.embed_sentence(query)
    
    # Step 2: Perform FAISS search
    query_embedding = np.array([query_embedding])  # FAISS expects a 2D array
    distances, indices = faiss_index.search(query_embedding, top_k)
    
    # Step 3: Retrieve and return the top_k most similar chunks
    results = []
    for idx in indices[0]:
        if idx < len(groups):
            results.append(' '.join(groups[idx]))  # Join sentences in the chunk
    
    return results



# Example usage
user_query = "what is the real name of undertaker?"  # Example query

# Search in FAISS index for the best matching chunk
top_k_results = search_faiss_index(user_query, chunker, faiss_index, groups, top_k=5)

# Print the best result
print(f"Best matching chunk: {top_k_results}")





from transformers import pipeline
from langchain_community.llms import Ollama

def create_prompt(context, query):
    """
    Combine the best matching context and query into a prompt for the LLM.
    
    Args:
    - context (str): The best matching context retrieved from FAISS.
    - query (str): The user's query.
    
    Returns:
    - str: A well-structured prompt combining context and query.
    """
    prompt = f"Context: {context}\n\nQuestion: {query}\n\nAnswer:"
    return prompt

def generate_answer(prompt, model_name):
    """
    Generate an answer using an open-source LLM (like GPT-2).
    
    Args:
    - prompt (str): The prompt containing context and the query.
    - model_name (str): The name of the model to use (default: 'gpt2').
    
    Returns:
    - str: The generated answer from the LLM.
    """

    model = Ollama(model=model_name)
    result = model.invoke(prompt)
    #print(result)
    
    return result


prompt = create_prompt(top_k_results, user_query)

# Step 2: Generate the answer using an LLM
answer = generate_answer(prompt, model_name="mistral")  # You can replace 'gpt2' with another model

# Output the answer
print("Generated Answer:\n", answer)
