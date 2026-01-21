
from typing import List

def kmp(s: str) -> List[int]:

    n = len(s)
    res = [0] * n
    idx = 0

    for i in range(1, len(s)):
        while idx != 0 and s[i] != s[idx]:
            idx = res[idx - 1]
        
        if s[i] == s[idx]:
            idx += 1
        res[i] = idx
    
    return res

print(kmp("abab"))
