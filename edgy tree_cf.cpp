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

        configureTextField(upperSetupCodeTextField, placeholder: "Enter setup code")
        configureTextField(lowerSetupCodeTextField, placeholder: "Lower setup code")

        view.addSubview(upperSetupCodeTextField)
        view.addSubview(lowerSetupCodeTextField)

        setupUI()
        bindTextFields()
        
        DispatchQueue.main.asyncAfter(deadline: .now()+5) {
            self.upperSetupCodeTextField.text = "1234-567-890"
            self.lowerSetupCodeTextField.text = "1234-567-8"
            self.activateLowerTextField()
        }
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

        upperSetupCodeTextField.isUserInteractionEnabled = true
        upperSetupCodeTextField.becomeFirstResponder()

        lowerSetupCodeTextField.isHidden = true
        lowerSetupCodeTextField.isUserInteractionEnabled = false
    }

    func configureTextField(_ textField: UITextField, placeholder: String) {
        textField.placeholder = placeholder
        textField.borderStyle = .roundedRect
        textField.textAlignment = .center
        textField.font = .systemFont(ofSize: 16)
        textField.autocorrectionType = .no
        textField.autocapitalizationType = .none
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

// MARK: - Combine Bindings
private extension ViewController {
    func bindTextFields() {
        // Observe text changes for both fields
        let upperPublisher = NotificationCenter.default.publisher(for: UITextField.textDidChangeNotification, object: upperSetupCodeTextField)
            .compactMap { ($0.object as? UITextField)?.text }

        let lowerPublisher = NotificationCenter.default.publisher(for: UITextField.textDidChangeNotification, object: lowerSetupCodeTextField)
            .compactMap { ($0.object as? UITextField)?.text }

        // Lower → Upper transition when lower becomes empty
        lowerPublisher
            .sink { [weak self] text in
                guard let self = self else { return }
                if text.isEmpty && !self.lowerSetupCodeTextField.isHidden {
                    self.deactivateLowerTextField()
                }
            }
            .store(in: &cancellables)

        // Upper → Lower dynamic check: if user typed past 12, move overflow to lower
        upperPublisher
            .sink { [weak self] text in
                guard let self = self else { return }
                self.checkUpperOverflow(text: text)
            }
            .store(in: &cancellables)
    }
}

// MARK: - State Transitions
private extension ViewController {
    func activateLowerTextField() {
        guard lowerSetupCodeTextField.isHidden else { return }
        upperSetupCodeTextField.isUserInteractionEnabled = false
        upperSetupCodeTextField.resignFirstResponder()

        lowerSetupCodeTextField.isHidden = false
        lowerSetupCodeTextField.isUserInteractionEnabled = true
        lowerSetupCodeTextField.becomeFirstResponder()
    }

    func deactivateLowerTextField() {
        guard !lowerSetupCodeTextField.isHidden else { return }
        lowerSetupCodeTextField.resignFirstResponder()
        lowerSetupCodeTextField.isHidden = true
        lowerSetupCodeTextField.isUserInteractionEnabled = false

        upperSetupCodeTextField.isUserInteractionEnabled = true
        upperSetupCodeTextField.becomeFirstResponder()
    }

    /// Handles moving 13th+ character from upper to lower field
    func checkUpperOverflow(text: String) {
        let upperLimit = 12
        if text.count > upperLimit {
            let overflowIndex = text.index(text.startIndex, offsetBy: upperLimit)
            let overflow = String(text[overflowIndex...]) // characters beyond limit
            upperSetupCodeTextField.text = String(text[..<overflowIndex]) // trim upper to 12
            activateLowerTextField()
            // Append overflow to lower
            lowerSetupCodeTextField.text = (lowerSetupCodeTextField.text ?? "") + overflow
        }
    }
}

// MARK: - UITextFieldDelegate (Character Limits)
extension ViewController: UITextFieldDelegate {
    func textField(_ textField: UITextField, shouldChangeCharactersIn range: NSRange, replacementString string: String) -> Bool {

        let currentText = textField.text ?? ""
        let updatedLength = currentText.count - range.length + string.count

        if textField == upperSetupCodeTextField {
            return updatedLength <= 1000 // We allow large, actual overflow handled in checkUpperOverflow
        }

        if textField == lowerSetupCodeTextField {
            return updatedLength <= 10
        }

        return true
    }
}

*/
