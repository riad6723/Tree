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

//import UIKit
//
//// MARK: - First Page
//class ViewController: UIViewController {
//    
//    override func viewDidLoad() {
//        super.viewDidLoad()
//        view.backgroundColor = .systemBackground
//        title = "First Page"
//        
//        // 1. Create a button to trigger navigation
//        let button = UIButton(type: .system)
//        button.setTitle("Go to Second Page", for: .normal)
//        button.frame = CGRect(x: 0, y: 0, width: 200, height: 50)
//        button.center = view.center
//        button.addTarget(self, action: #selector(navigateToSecondPage), for: .touchUpInside)
//        
//        view.addSubview(button)
//    }
//    
//    // 2. Push the second view controller
//    @objc private func navigateToSecondPage() {
//        let secondVC = SecondViewController()
//        self.navigationController?.pushViewController(secondVC, animated: true)
//    }
//}
//
//// MARK: - Second Page (With Intercepted Back Button)
//class SecondViewController: UIViewController {
//    
//    override func viewDidLoad() {
//        super.viewDidLoad()
//        view.backgroundColor = .systemGroupedBackground
//        title = "Second Page"
//        
//        setupNativeBackAction()
//    }
//    
//    // Disable swipe-to-go-back to prevent bypassing the alert
//    override func viewDidAppear(_ animated: Bool) {
//        super.viewDidAppear(animated)
//        self.navigationController?.interactivePopGestureRecognizer?.isEnabled = false
//    }
//    
//    // Re-enable swipe-to-go-back when leaving
//    override func viewWillDisappear(_ animated: Bool) {
//        super.viewWillDisappear(animated)
//        self.navigationController?.interactivePopGestureRecognizer?.isEnabled = true
//    }
//
//    private func setupNativeBackAction() {
//        // iOS 16+ native back button interception
//        if #available(iOS 16.0, *) {
//            self.navigationItem.backAction = UIAction { [weak self] _ in
//                self?.showConfirmationAlert()
//            }
//        } else {
//            print("Running on iOS 15 or lower - fallback needed here.")
//        }
//    }
//
//    private func showConfirmationAlert() {
//        let alert = UIAlertController(
//            title: "Are you sure?",
//            message: "Any unsaved changes will be lost.",
//            preferredStyle: .alert
//        )
//        
//        alert.addAction(UIAlertAction(title: "Cancel", style: .cancel, handler: nil))
//        
//        alert.addAction(UIAlertAction(title: "OK", style: .destructive, handler: { [weak self] _ in
//            self?.navigationController?.popViewController(animated: true)
//        }))
//        
//        present(alert, animated: true, completion: nil)
//    }
//}



import UIKit

// MARK: - VC1 (The Root)
class ViewController: UIViewController {
    override func viewDidLoad() {
        super.viewDidLoad()
        view.backgroundColor = .systemBackground
        title = "VC 1"
        
        let button = UIButton(type: .system)
        button.setTitle("Go to VC 2", for: .normal)
        button.frame = CGRect(x: 0, y: 0, width: 200, height: 50)
        button.center = view.center
        button.addTarget(self, action: #selector(pushVC2), for: .touchUpInside)
        view.addSubview(button)
    }
    
    @objc private func pushVC2() {
        navigationController?.pushViewController(VC2(), animated: true)
    }
}

// MARK: - VC2 (The Middleman)
class VC2: UIViewController {
    override func viewDidLoad() {
        super.viewDidLoad()
        view.backgroundColor = .systemGray6
        title = "VC 2"
        
        let button = UIButton(type: .system)
        button.setTitle("Go to VC 3", for: .normal)
        button.frame = CGRect(x: 0, y: 0, width: 200, height: 50)
        button.center = view.center
        button.addTarget(self, action: #selector(pushVC3), for: .touchUpInside)
        view.addSubview(button)
    }
    
    @objc private func pushVC3() {
        navigationController?.pushViewController(VC3(), animated: true)
    }
}

// MARK: - VC3 (The Decision Maker)
class VC3: UIViewController {
    
    // Toggle this boolean to test your two conditions!
    var shouldShowPopup = false
    
    override func viewDidLoad() {
        super.viewDidLoad()
        view.backgroundColor = .systemGroupedBackground
        title = "VC 3"
        
        setupNativeBackAction()
    }
    
    // Prevent swiping back to VC2
    override func viewDidAppear(_ animated: Bool) {
        super.viewDidAppear(animated)
        self.navigationController?.interactivePopGestureRecognizer?.isEnabled = false
    }
    
    override func viewWillDisappear(_ animated: Bool) {
        super.viewWillDisappear(animated)
        self.navigationController?.interactivePopGestureRecognizer?.isEnabled = true
    }

    private func setupNativeBackAction() {
        if #available(iOS 16.0, *) {
            self.navigationItem.backAction = UIAction { [weak self] _ in
                self?.handleBackTapped()
            }
        }
    }

    private func handleBackTapped() {
        if shouldShowPopup {
            // Condition A: Show popup, then go to VC1
            showConfirmationAlert()
        } else {
            // Condition B: No popup, go directly to VC1
            goBackToVC1()
        }
    }

    private func showConfirmationAlert() {
        let alert = UIAlertController(
            title: "Warning",
            message: "Do you want to discard and return to the start?",
            preferredStyle: .alert
        )
        
        alert.addAction(UIAlertAction(title: "Cancel", style: .cancel, handler: nil))
        
        alert.addAction(UIAlertAction(title: "OK", style: .destructive, handler: { [weak self] _ in
            self?.goBackToVC1()
        }))
        
        present(alert, animated: true, completion: nil)
    }
    
    // The routing magic
    private func goBackToVC1() {
        // Option 1: If VC1 is the very first screen in your entire Navigation Controller
        //self.navigationController?.popToRootViewController(animated: true)
        
        //Option 2: If VC1 is NOT the root, but just somewhere earlier in the stack,
        //you can search the stack for it and pop directly to it:
         
        if let vc1 = self.navigationController?.viewControllers.first(where: { $0 is ViewController }) {
            self.navigationController?.popToViewController(vc1, animated: true)
        }
        
    }
}


*/

