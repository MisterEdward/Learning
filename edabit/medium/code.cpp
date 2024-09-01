string tweakLetters(string s, vector<int> arr) {
    for(size_t i = 0; i < s.size(); i++) {
        s[i] += arr[i];
    }

    return s;
}