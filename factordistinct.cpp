#include<iostream>
#include<sstream>
#include<iterator>
#include<numeric>
#include<vector>
#include<stack>
#include<algorithm>

using namespace std;
typedef unsigned long long ll;
typedef vector<int> vi;

// finds the maximum number of parts in a partition of v into vectors
// with non-negative integer coordinates all greater than x (according
// to the order determined by next), and also returns it
pair<int, vector<vi>> solve(vi v, vi x) {

  auto sub = [](vi v, const vi &y) {
    for (int i = 0; i < y.size(); i++)
      if (!v[y[i]]--)
	return vi();
    return v;
  };

  auto next = [](vi v, int n) {
    int i = 0;
    while (i < v.size() && v[i] == n - 1) i++;
    if (i == v.size())
      return vi(v.size() + 1, 0);
    v[i] += 1;
    for (int j = 0; j < i; j++)
      v[j] = v[i];
    return v;
  };

  vector<vi> solution, prefix;
  function<int(vi, vi, int)> backtrack = [&](vi v, vi x, int tobeat) -> int {
    if (prefix.size() > solution.size()) {
      solution = prefix;
    }
    vi succ = next(x, v.size());
    int sum = accumulate(v.begin(), v.end(), 0, plus<int>());
    if (tobeat >= sum/succ.size()) // prune
      return tobeat;
    vi w = sub(v, succ);
    if (!w.empty()) {
      prefix.push_back(succ);
      tobeat = 1 + backtrack(w, succ, max(tobeat-1,0));
      prefix.pop_back();
    }
    return backtrack(v, succ, tobeat);
  };

  return {backtrack(v, x, 0), solution};
}

int main(int argc, char* argv[]) {

  for (int i = 1; i < argc; i++) {
    ll N; istringstream iss(argv[i]);
    iss >> N;
    if (iss.fail() || N == 0 || N == 1)
      continue;

    vector<ll> singletons, rest;
    vi v; ll n = N;
    for (ll p = 2; p*p <= n; ++p) {
      int e = 0;
      while (n % p == 0) n /= p, ++e;
      if (e) {
	singletons.push_back(p);
	if (e > 1)
	  rest.push_back(p), v.push_back(e-1);
      }
    }
    if (n != 1) singletons.push_back(n);

    vector<vi> solution = solve(v, vi(1, v.size()-1)).second;

    for (int i = 0; i < solution.size(); i++) {
      ll t = 1;
      for (int j = 0; j < solution[i].size(); j++)
	t *= rest[solution[i][j]];
      singletons.push_back(t);
    }

    ll prod = 1;
    for (int i = 0; i < singletons.size(); i++)
      prod *= singletons[i];
    singletons.back() *= N/prod;
    sort(singletons.begin(), singletons.end());

    auto print = [](vector<ll> v) {
      copy(v.begin(), v.end(), ostream_iterator<ll>(cout, " "));
    };

    cout << N << ": "; print(singletons);
    cout << endl;
  }

  return 0;
}
