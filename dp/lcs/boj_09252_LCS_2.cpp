﻿/*
BOJ 9252 — LCS 2
Topic: DP | LCS | Reconstruction
Folder: dp/lcs/

⏱ 시간복잡도: O(n·m)
💾 공간복잡도: O(n·m)

📌 핵심 아이디어
- 2D DP: lcs[i][j] = LCS( s1[0..i-1], s2[0..j-1] ) 길이.
- 복원: i=n, j=m에서 시작해
  - s1[i-1]==s2[j-1] → 문자를 답에 push_back하고 i--, j--.
  - 아니면 lcs[i][j-1]와 lcs[i-1][j] 중 큰 쪽으로 이동(같으면 한쪽을 선택).

⚠️ 주의할 점
- 인덱싱: 비교 시 s1[i-1], s2[j-1]로 접근.
- 출력 규칙(중요): LCS 길이가 0이면 **두 번째 줄(문자열)을 출력하지 않음**.
- 복원 시 tie-break는 임의 선택 가능(문제는 임의의 LCS 허용). 현재 코드는 j-1을 우선(>=)으로 택함.
- 메모리 O(n·m). 길이가 매우 크다면 복원용 parent만 저장하거나 경로 압축 기법 고려.

✔️ 지문 힌트
- 첫 줄: LCS 길이
- 둘째 줄: LCS 문자열(길이>0일 때만)
*/

// 2025-09-28 D+3 REVIEW

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	string s1, s2;
	cin >> s1 >> s2;

	int n = (int)s1.size(), m = (int)s2.size();

	vector<vector<int>> lcs(n + 1, vector<int>(m + 1, 0));
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= m; j++)
		{
			if (s1[i - 1] == s2[j - 1]) lcs[i][j] = lcs[i - 1][j - 1] + 1;	// 비교할 때 s1과 s2는 index에 -1 해야 함
			else lcs[i][j] = max(lcs[i - 1][j], lcs[i][j - 1]);
		}
	}

	string ans;
	int i = n, j = m;
	while (i > 0 && j > 0)
	{
		if (s1[i - 1] == s2[j - 1])	// 마찬가지
		{
			ans.push_back(s1[i - 1]);
			i--;
			j--;
		}
		else
		{
			if (lcs[i][j - 1] >= lcs[i - 1][j]) j--;
			else i--;
		}
	}
	reverse(ans.begin(), ans.end());
	cout << lcs[n][m] << "\n";
	if (lcs[n][m] > 0) cout << ans << "\n";
}

// 2025-09-25 D+0 REVIEW

// #include <iostream>
// #include <string>
// #include <vector>
// #include <algorithm>
// 
// using namespace std;
// 
// int main()
// {
// 	ios::sync_with_stdio(false);
// 	cin.tie(nullptr);
// 
// 	string s1, s2;
// 	cin >> s1 >> s2;
// 	int n = (int)s1.size(), m = (int)s2.size();
// 
// 	string ans = "";
// 	vector<vector<int>> lcs(n + 1, vector<int>(m + 1, 0));
// 
// 	for (int i = 1; i <= n; i++)
// 	{
// 		for (int j = 1; j <= m; j++)
// 		{
// 			if (s1[i - 1] == s2[j - 1]) lcs[i][j] = lcs[i - 1][j - 1] + 1;
// 			else lcs[i][j] = max(lcs[i - 1][j], lcs[i][j - 1]);
// 		}
// 	}
// 
// 	ans.reserve(lcs[n][m]);
// 	int i = n, j = m;
// 	while (i > 0 && j > 0)
// 	{
// 		if (s1[i-1] == s2[j-1])
// 		{
// 			ans.push_back(s1[i - 1]);
// 			i--; j--;
// 		}
// 		else
// 		{
// 			if (lcs[i - 1][j] > lcs[i][j - 1]) i--;
// 			else j--;
// 		}
// 	}
// 	reverse(ans.begin(), ans.end());
// 
// 	cout << lcs[n][m] << "\n";
// 	if (!ans.empty()) cout << ans << "\n";
// }

// 2025-09-25 ORIGINAL

// #include <iostream>
// #include <string>
// #include <vector>
// #include <algorithm>
// 
// using namespace std;
// 
// int main()
// {
// 	ios::sync_with_stdio(false);
// 	cin.tie(nullptr);
// 
// 	string s1, s2;
// 	cin >> s1 >> s2;
// 	int n = (int)s1.size(), m = (int)s2.size();
// 
// 	vector<vector<int>> lcs(n + 1, vector<int>(m + 1, 0));
// 	
// 	for (int i = 1; i <= n; i++)
// 	{
// 		for (int j = 1; j <= m; j++)
// 		{
// 			if (s1[i - 1] == s2[j - 1]) lcs[i][j] = lcs[i - 1][j - 1] + 1;
// 			else lcs[i][j] = max(lcs[i - 1][j], lcs[i][j - 1]);
// 		}
// 	}
// 
// 	int i = n, j = m;
// 	string ans;
// 	while (i > 0 && j > 0)
// 	{
// 		if (s1[i - 1] == s2[j - 1])
// 		{
// 			ans.push_back(s1[i - 1]);
// 			i--;  j--;
// 		}
// 		else
// 		{
// 			if (lcs[i][j - 1] > lcs[i - 1][j]) j--;
// 			else i--;
// 		}
// 	}
// 	reverse(ans.begin(), ans.end());
// 
// 	cout << lcs[n][m] << "\n";
// 	if(!ans.empty()) cout << ans << "\n";
// }
