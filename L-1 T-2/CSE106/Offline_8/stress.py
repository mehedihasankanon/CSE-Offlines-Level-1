import random

# Function to check if two bases match
def match(a, b):
    return a == b

# Smith-Waterman algorithm for local alignment
def local_alignment(s1, s2, match_score, mismatch_penalty, gap_penalty):
    n, m = len(s1), len(s2)
    dp = [[0] * (m + 1) for _ in range(n + 1)]
    traceback = [[' '] * (m + 1) for _ in range(n + 1)]
    max_score = 0
    max_i, max_j = 0, 0
    
    for i in range(1, n + 1):
        for j in range(1, m + 1):
            diag = dp[i - 1][j - 1] + (match_score if match(s1[i - 1], s2[j - 1]) else mismatch_penalty)
            up = dp[i - 1][j] + gap_penalty
            left = dp[i][j - 1] + gap_penalty
            dp[i][j] = max(0, diag, up, left)
            if dp[i][j] == 0:
                traceback[i][j] = 'S'
            elif dp[i][j] == diag:
                traceback[i][j] = 'D'
            elif dp[i][j] == up:
                traceback[i][j] = 'U'
            else:
                traceback[i][j] = 'L'
            if dp[i][j] > max_score:
                max_score = dp[i][j]
                max_i, max_j = i, j
    
    t1, t2 = [], []
    i, j = max_i, max_j
    while i > 0 and j > 0 and dp[i][j] > 0:
        if traceback[i][j] == 'D':
            t1.append(s1[i - 1])
            t2.append(s2[j - 1])
            i -= 1
            j -= 1
        elif traceback[i][j] == 'U':
            t1.append(s1[i - 1])
            t2.append('-')
            i -= 1
        elif traceback[i][j] == 'L':
            t1.append('-')
            t2.append(s2[j - 1])
            j -= 1
    
    t1 = ''.join(t1[::-1])
    t2 = ''.join(t2[::-1])
    return t1, t2, max_score

# Needleman-Wunsch algorithm for global alignment
def global_alignment(s1, s2, match_score, mismatch_penalty, gap_penalty):
    n, m = len(s1), len(s2)
    dp = [[0] * (m + 1) for _ in range(n + 1)]
    traceback = [[' '] * (m + 1) for _ in range(n + 1)]
    
    # Initialize first row and column
    for i in range(n + 1):
        dp[i][0] = i * gap_penalty
        traceback[i][0] = 'U'
    for j in range(m + 1):
        dp[0][j] = j * gap_penalty
        traceback[0][j] = 'L'
    
    # Fill DP matrix
    for i in range(1, n + 1):
        for j in range(1, m + 1):
            diag = dp[i - 1][j - 1] + (match_score if match(s1[i - 1], s2[j - 1]) else mismatch_penalty)
            up = dp[i - 1][j] + gap_penalty
            left = dp[i][j - 1] + gap_penalty
            dp[i][j] = max(diag, up, left)
            if dp[i][j] == diag:
                traceback[i][j] = 'D'
            elif dp[i][j] == up:
                traceback[i][j] = 'U'
            else:
                traceback[i][j] = 'L'
    
    # Traceback from bottom-right
    t1, t2 = [], []
    i, j = n, m
    while i > 0 or j > 0:
        if i > 0 and j > 0 and traceback[i][j] == 'D':
            t1.append(s1[i - 1])
            t2.append(s2[j - 1])
            i -= 1
            j -= 1
        elif i > 0 and traceback[i][j] == 'U':
            t1.append(s1[i - 1])
            t2.append('-')
            i -= 1
        else:
            t1.append('-')
            t2.append(s2[j - 1])
            j -= 1
    
    t1 = ''.join(t1[::-1])
    t2 = ''.join(t2[::-1])
    return t1, t2, dp[n][m]

# Generate random DNA sequence
def generate_dna(length):
    bases = ['A', 'T', 'C', 'G']
    return ''.join(random.choice(bases) for _ in range(length))

# Generate test cases
def generate_test_cases():
    test_cases = [
        ("AGACTAGTTAC", "CGAAGTT", 1, -1, -2),
        ("", "", 1, -1, -2),
        ("ACTG", "", 1, -1, -2),
        ("A", "A", 1, -1, -2),
        ("A", "C", 1, -1, -2),
        ("AAAA", "CCCC", 1, -1, -2),
        ("ACTG", "ACTG", 1, -1, -2),
        ("ACTG", "AG", 1, -1, -2),
        ("ACTG", "AGTC", 2, -3, -4),
        (generate_dna(100), generate_dna(100), 1, -1, -2)
    ]
    
    # Write inputs to stress.txt
    with open("stress.txt", "w") as f:
        f.write(f"{len(test_cases)}\n")
        for s1, s2, match_score, mismatch_penalty, gap_penalty in test_cases:
            f.write(f"{s1}\n")
            f.write(f"{s2}\n")
            f.write(f"{match_score}\n")
            f.write(f"{mismatch_penalty}\n")
            f.write(f"{gap_penalty}\n")
    
    # Write expected outputs to stress_out.txt
    with open("stress_out.txt", "w") as f:
        for idx, (s1, s2, match_score, mismatch_penalty, gap_penalty) in enumerate(test_cases, 1):
            # Local alignment
            t1_local, t2_local, max_score_local = local_alignment(s1, s2, match_score, mismatch_penalty, gap_penalty)
            # Global alignment
            t1_global, t2_global, max_score_global = global_alignment(s1, s2, match_score, mismatch_penalty, gap_penalty)
            # Write outputs
            f.write(f"Test Case {idx}:\n")
            f.write(f"Local Alignment:\n")
            f.write(f"{t1_local}\n")
            f.write(f"{t2_local}\n")
            f.write(f"Local Maximum Score: {max_score_local}\n")
            f.write(f"Global Alignment:\n")
            f.write(f"{t1_global}\n")
            f.write(f"{t2_global}\n")
            f.write(f"Global Maximum Score: {max_score_global}\n\n")
    
    print("Test cases written to stress.txt and expected outputs (local and global alignments) to stress_out.txt")

# Run the generator
if __name__ == "__main__":
    generate_test_cases()