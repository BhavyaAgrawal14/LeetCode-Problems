class Solution {
public:

    set<string> parse(string &s, int &i) {

        // Result of the current expression
        set<string> result;

        // Used for concatenation
        set<string> current = {""};

        while (i < s.size() && s[i] != '}') {

            if (s[i] == ',') {
                // Union: save current possibilities into result
                result.insert(current.begin(), current.end());

                current.clear();
                current.insert("");

                i++;
            }

            else if (s[i] == '{') {
                i++; // skip '{'

                // Parse everything inside braces
                set<string> inside = parse(s, i);

                i++; // skip '}'

                // Concatenate current × inside
                set<string> next;

                for (string a : current) {
                    for (string b : inside) {
                        next.insert(a + b);
                    }
                }

                current = next;
            }

            else {
                // Lowercase letter
                string ch(1, s[i]);

                set<string> next;

                for (string a : current) {
                    next.insert(a + ch);
                }

                current = next;

                i++;
            }
        }

        // Add the last concatenation part
        result.insert(current.begin(), current.end());

        return result;
    }

    vector<string> braceExpansionII(string expression) {

        int i = 0;

        set<string> ans = parse(expression, i);

        return vector<string>(ans.begin(), ans.end());
    }
};