class MovieRentingSystem {
    unordered_map<int, set<pair<int,int>>> available;
    set<tuple<int,int,int>> rented;
    map<pair<int,int>, int> priceMap;

public:
    MovieRentingSystem(int n, vector<vector<int>>& entries) {
        for (auto &e : entries) {
            int shop = e[0], movie = e[1], price = e[2];
            available[movie].insert({price, shop});
            priceMap[{shop, movie}] = price;
        }
    }
    
    vector<int> search(int movie) {
        vector<int> res;
        if (!available.count(movie)) return res;
        
        int count = 0;
        for (auto &p : available[movie]) {
            res.push_back(p.second);
            if (++count == 5) break;
        }
        return res;
    }
    
    void rent(int shop, int movie) {
        int price = priceMap[{shop, movie}];
        available[movie].erase({price, shop});
        rented.insert({price, shop, movie});
    }
    
    void drop(int shop, int movie) {
        int price = priceMap[{shop, movie}];
        rented.erase({price, shop, movie});
        available[movie].insert({price, shop});
    }
    
    vector<vector<int>> report() {
        vector<vector<int>> res;
        int count = 0;
        for (auto &t : rented) {
            res.push_back({get<1>(t), get<2>(t)});
            if (++count == 5) break;
        }
        return res;
    }
};
