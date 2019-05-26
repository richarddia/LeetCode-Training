class Solution {
public:
    vector<int> rearrangeBarcodes(vector<int>& barcodes) {
        unordered_map<int, int> umap;
        int n = barcodes.size();
        for (auto& x : barcodes ) ++umap[x];
        // c++ 里面lambda 函数如果想用out-of-scope variable, 需要用[=]或者[&]
        // https://stackoverflow.com/questions/7627098/what-is-a-lambda-expression-in-c11/7627218#7627218
        sort(barcodes.begin(), barcodes.end(), [&umap](int& x, int& y){
            if (umap[x] != umap[y] ) return umap[x] > umap[y];
            else return x < y;
        });
        vector<int> res(n);
        int pt = 0;
        for ( int j = 0; j < n; ++j ) {
            res[pt] = barcodes[j];
            pt += 2;
            if ( pt >= n ) pt = 1;
        }
        return res;
    }
};