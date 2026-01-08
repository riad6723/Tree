#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define ull unsigned long long
#define pb push_back
#define ps push
#define pf push_front
#define mp make_pair
#define And &&
#define Or ||
#define inf INT_MAX
#define sz(name) name.size()
#define len(name) name.length()
#define ig cin.ignore()
#define sc1(name) scanf("%d",&name)
#define sc2(name1,name2) scanf("%d%d",&name1,&name2)
#define sc3(name1,name2,name3) scanf("%d%d%d",&name1,&name2,&name3)
#define scl1(name) scanf("%lld",&name)
#define scl2(name1,name2) scanf("%lld%lld",&name1,&name2)
#define scl3(name1,name2,name3) scanf("%lld%lld%lld",&name1,&name2,&name3)
#define Sort(name) sort(name.begin(),name.end())
#define For(name,start,finish) for(int name=start;name<finish;name++)
#define Forr(name,start,finish) for(int name=start;name>=finish;name--)
#define fast_in_out ios_base::sync_with_stdio(false);cin.tie(0);cout.tie(0);


int row[]={0,1,0,-1};
int col[]={1,0,-1,0};

const ll N=1e6+10;
const ll M=1e18+7;
const ll H=1e9+7;
const ll base=131;

ll logx(ll a,ll bs){return log(a)/log(bs);}
ll Max(ll a,ll b){if(a>b)return a;return b;}
ll Min(ll a,ll b){if(a>b)return b;return a;}
ll big_mul(ll a,ll b,ll m){ll x=0,y=a%m;while(b>0){if(b&1)x=(x+y)%m;y=(2*y)%m;b>>=1;}return x%m;}
ll big_mod(ll a,ll b,ll m){ll x=1,y=a%m;while(b>0){if(b&1)x=(x*y)%m;y=(y*y)%m;b>>=1;}return x%m;}
ll Big_mod(ll a,ll b,ll m){ll x=1,y=a%m;while(b>0){if(b&1)x=big_mul(x,y,m);y=big_mul(y,y,m);b>>=1;}return x%m;}
ll mod_inverse(ll a,ll m){return big_mod(a,m-2,m);}  //a^-1 mod m = a^(m-2) mod m
ll GCD(ll a,ll b){if(!a)return b;return GCD(b%a,a);}

vector<bool> vis(N);
vector<vector<int> > graph(N);

ll dfs(int node)
{
	ll cnt=0;
	vis[node]=true;

	For(i,0,sz(graph[node]))
	{
		int p=graph[node][i];

		if(vis[p]==false)
		cnt+=dfs(p);
	}

	return cnt+1;
}

int main()
{

	fast_in_out;

	int n,m;
	cin>>n>>m;

	For(i,1,n)
	{
		int a,b,x;
		cin>>a>>b>>x;

		if(!x)
		{
			graph[a].pb(b);
			graph[b].pb(a);
		}
	}

 	ll ans=big_mod(n,m,H);

	For(i,1,n+1)
	{
		if(vis[i]==false)
		ans=(ans-big_mod(dfs(i),m,H)+H)%H;
	}

	cout<<ans<<endl;

	return 0;

}

/*

import UIKit
import Combine

final class ViewController: UIViewController {
    // MARK: - UI
    private let upperSetupCodeTextField = UITextField()
    private let lowerSetupCodeTextField = UITextField()
    
    // MARK: - Combine
    private var cancellables = Set<AnyCancellable>()
    
    // MARK: - Lifecycle
    override func viewDidLoad() {
        super.viewDidLoad()
        view.backgroundColor = .systemBackground
        
        configureTextField(upperSetupCodeTextField, placeholder: "xxxx-xxx-xxxx")
        configureTextField(lowerSetupCodeTextField, placeholder: "xxxx-xxx-xx-x")
        
        view.addSubview(upperSetupCodeTextField)
        view.addSubview(lowerSetupCodeTextField)
        
        setupUI()
        bindTextFields()
        
//        DispatchQueue.main.asyncAfter(deadline: .now() + 3) {
//            self.upperSetupCodeTextField.text = "1234-567-8901"
//            self.lowerSetupCodeTextField.text = "1234-567-89-0"
//            self.activateLowerTextField()
//        }
    }
    
    override func viewDidLayoutSubviews() {
        super.viewDidLayoutSubviews()
        layoutTextFields()
    }
}

// MARK: - UI Setup
private extension ViewController {
    func setupUI() {
        upperSetupCodeTextField.delegate = self
        lowerSetupCodeTextField.delegate = self
        upperSetupCodeTextField.keyboardType = .numberPad
        upperSetupCodeTextField.isUserInteractionEnabled = true
        upperSetupCodeTextField.becomeFirstResponder()
        
        lowerSetupCodeTextField.isHidden = true
        lowerSetupCodeTextField.isUserInteractionEnabled = false
        lowerSetupCodeTextField.keyboardType = .numberPad
    }
    
    func configureTextField(_ textField: UITextField, placeholder: String) {
        textField.placeholder = placeholder
        textField.borderStyle = .roundedRect
        textField.textAlignment = .center
        textField.font = .monospacedDigitSystemFont(ofSize: 18, weight: .medium) // Better for fixed formats
        textField.autocorrectionType = .no
        textField.returnKeyType = .done
    }
    
    func layoutTextFields() {
        let width: CGFloat = 300
        let height: CGFloat = 50
        let spacing: CGFloat = 20
        let x = (view.bounds.width - width) / 2
        let y: CGFloat = 200
        
        upperSetupCodeTextField.frame = CGRect(x: x, y: y, width: width, height: height)
        lowerSetupCodeTextField.frame = CGRect(x: x, y: upperSetupCodeTextField.frame.maxY + spacing, width: width, height: height)
    }
}

// MARK: - Combine Bindings & Logic
private extension ViewController {
    func bindTextFields() {
        // Upper Publisher
        NotificationCenter.default.publisher(for: UITextField.textDidChangeNotification, object: upperSetupCodeTextField)
            .compactMap { ($0.object as? UITextField)?.text }
            .sink { [weak self] text in
                guard let self = self else { return }
                let digits = text.filter { $0.isNumber }
                
                // Format UI
                self.upperSetupCodeTextField.text = self.format(digits: digits, pattern: "xxxx-xxx-xxxx")
                
                // Handle Overflow (if digits exceed 11)
                if digits.count > 11 {
                    self.checkUpperOverflow(digits: digits)
                }
            }
            .store(in: &cancellables)
        
        // Lower Publisher
        NotificationCenter.default.publisher(for: UITextField.textDidChangeNotification, object: lowerSetupCodeTextField)
            .compactMap { ($0.object as? UITextField)?.text }
            .sink { [weak self] text in
                guard let self = self else { return }
                let digits = text.filter { $0.isNumber }
                
                // Format UI
                self.lowerSetupCodeTextField.text = self.format(digits: digits, pattern: "xxxx-xxx-xx-x")
                
                // Transition back if empty
                if digits.isEmpty && !self.lowerSetupCodeTextField.isHidden {
                    self.deactivateLowerTextField()
                }
            }
            .store(in: &cancellables)
    }
    
    /// Generic formatter that maps digits into a pattern
    func format(digits: String, pattern: String) -> String {
        var result = ""
        var digitIndex = digits.startIndex
        
        for char in pattern {
            guard digitIndex < digits.endIndex else { break }
            if char == "x" {
                result.append(digits[digitIndex])
                digitIndex = digits.index(after: digitIndex)
            } else {
                result.append(char) // Likely a hyphen
            }
        }
        return result
    }
    
    func checkUpperOverflow(digits: String) {
        let limit = 11
        let overflowDigits = String(digits.suffix(digits.count - limit))
        let keptDigits = String(digits.prefix(limit))
        
        // Update Upper to its max formatted state
        upperSetupCodeTextField.text = format(digits: keptDigits, pattern: "xxxx-xxx-xxxx")
        
        activateLowerTextField()
        
        // Push overflow to lower and format it
        let existingLower = (lowerSetupCodeTextField.text ?? "").filter { $0.isNumber }
        let newLowerDigits = existingLower + overflowDigits
        lowerSetupCodeTextField.text = format(digits: newLowerDigits, pattern: "xxxx-xxx-xx-x")
    }
}

// MARK: - State Transitions
private extension ViewController {
    func activateLowerTextField() {
        guard lowerSetupCodeTextField.isHidden else { return }
        
        // 1. Prepare the lower field first
        lowerSetupCodeTextField.isHidden = false
        lowerSetupCodeTextField.isUserInteractionEnabled = true
        
        // 2. Transfer focus DIRECTLY (Do not call resignFirstResponder on upper)
        lowerSetupCodeTextField.becomeFirstResponder()
        
        // 3. Clean up the upper field
        upperSetupCodeTextField.isUserInteractionEnabled = false
    }
    
    func deactivateLowerTextField() {
        guard !lowerSetupCodeTextField.isHidden else { return }
        
        // 1. Enable the upper field first
        upperSetupCodeTextField.isUserInteractionEnabled = true
        
        // 2. Transfer focus DIRECTLY
        upperSetupCodeTextField.becomeFirstResponder()
        
        // 3. Clean up the lower field
        lowerSetupCodeTextField.isHidden = true
        lowerSetupCodeTextField.isUserInteractionEnabled = false
    }
}

// MARK: - UITextFieldDelegate
extension ViewController: UITextFieldDelegate {
    func textField(_ textField: UITextField, shouldChangeCharactersIn range: NSRange, replacementString string: String) -> Bool {
        // Prevent non-numeric entry via keyboard
        let allowedCharacters = CharacterSet.decimalDigits
        let characterSet = CharacterSet(charactersIn: string)
        return allowedCharacters.isSuperset(of: characterSet)
    }
}

*/

