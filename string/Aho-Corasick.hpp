// 参考：https://atcoder.jp/contests/abc419/submissions/68578414

// Aho-Corasick法：複数のパターン文字列を同時に探し出すアルゴリズム
class AhoCorasick {
private:
    static const int ALPHABET_SIZE = 26;

    // Aho-Corasick Automaton
    struct Node {
        vector<int> next; // トライの遷移。next[c]：現在のノードから文字 c に対応する子ノードのインデックス
        int fail; // 失敗リンク
        int output_mask; // i 番目のパターンがこのノードまでの文字列の接尾辞として出現する場合、i 番目のビットを 1 に立てる
    
        Node() : fail(0), output_mask(0) {
            next.assign(ALPHABET_SIZE, 0);
        }
    };

    vector<Node> trie; // Aho-Corasickオートマトンのすべてのノードを格納する動的な配列

    int char_to_int(char c) {
        return c - 'a';
    }

public:
    // コンストラクタ
    AhoCorasick() {
        trie.emplace_back(); // ルートノードを追加
    }

    // 与えられたパターン文字列をトライに挿入し、その最終ノードにパターンIDの情報を付与
    void add_string(const string& s, int pattern_id) {
        int node = 0;
        for (char c : s) {
            int char_idx = char_to_int(c);
            if (trie[node].next[char_idx] == 0) {
                trie[node].next[char_idx] = trie.size();
                trie.emplace_back();
            }
            node = trie[node].next[char_idx];
        }
        trie[node].output_mask |= (1 << pattern_id);
    }

    // 失敗リンクと出力情報を構築
    void build_failure_links() {
        queue<int> q;
        for (int i = 0; i < ALPHABET_SIZE; ++i) {
            if (trie[0].next[i] != 0) {
                q.push(trie[0].next[i]);
            }
        }
    
        while (!q.empty()) {
            int u = q.front();
            q.pop();
    
            trie[u].output_mask |= trie[trie[u].fail].output_mask; // 失敗リンク先ノードの出力情報も加える
    
            for (int i = 0; i < ALPHABET_SIZE; ++i) {
                if (trie[u].next[i] != 0) {
                    int v = trie[u].next[i];
                    trie[v].fail = trie[trie[u].fail].next[i];
                    q.push(v);
                } else {
                    trie[u].next[i] = trie[trie[u].fail].next[i];
                }
            }
        }
    }

    // Aho-Corasickオートマトンの状態遷移
    int next_state(int current_node, char c) {
        return trie[current_node].next[char_to_int(c)];
    }

    // 現在の状態の出力マスクを取得
    int get_output_mask(int node) const {
        return trie[node].output_mask;
    }

    // ノード数を取得
    size_t size() const {
        return trie.size();
    }
};
