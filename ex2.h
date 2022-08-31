//
// Created by USER on 8/25/2022.
//

#ifndef PRACTICE_EX2_H
#define PRACTICE_EX2_H

#include <fstream>
#include <algorithm>
#include <vector>

void ex2(string file_name){
    fstream file_content(file_name);
    vector<string> output(1024), input(1024);
    vector<string>::iterator iter;

    string buff;
    while(file_content >> buff){
        input.push_back(buff);
    }

    iter = unique_copy(input.begin(), input.end(), output.begin());
    output.resize(distance(output.begin(), iter));

    while(1){
        cout<<iter->data() <<" ";
        iter--;
        if(iter == output.begin()){
            cout<<iter->data()<<endl;
            break;
        }
    }
}
template<class InIter, class OutIter, class Comparator>
void SortCopy( InIter first, InIter last, OutIter result, Comparator cmp){
    InIter temp = first;
    OutIter start_res = result;
    while(1){
        *result = *temp;
        result++;
        temp++;
        if(temp == last){
            *result = *temp;
            break;
        }
    }
    sort(start_res, result, cmp);
}

template<class IterIn, class IterOut>
void keep_it_real(IterIn first, IterIn last, IterOut out) {
    std::vector<std::pair<IterIn, int> > s(last - first);
    for (int i = 0; i < s.size(); ++i)
        s[i] = std::make_pair(first + i, i);
    sort(s.begin(),s.end(), [](pair<IterIn,int> a,pair<IterIn,int> b  ){return a.first<b.first;});

    for(int i=0; i<s.size(); i++) {
        cout << s[i].first << " " << s[i].second << endl;
        *out = s[i];
        out++;
    }
}
int ex2_2(void) {
    const int SIZE = 64;
    const double eps = 1e-2;
    vector<double> V;
    srand(time(NULL));
    for (int i=0 ; i<SIZE ; i++)
        V.push_back(static_cast<double>(rand())/RAND_MAX);
    /*
    TODO : std::replace_if a vector's coordinate is lower than eps.
     */
    replace_if(V.begin(), V.end(), [eps](double a){return eps > a ;},0);
    ostream_iterator<double> out (cout, " ");
    copy(V.begin(), V.end(), out);
    cout << "\r\n";
    return 0;
}
template<typename MapIt>
void showCommonWords(MapIt begin, MapIt end, const std::size_t n) {
    std::vector<MapIt> wordIters;
    wordIters.reserve(std::distance(begin, end));
    for (auto i = begin; i != end; ++i) wordIters.push_back(i);
    /*
    TODO: std::partial_sort n element in wordIters according to \second\
    */
    partial_sort(wordIters.begin(), wordIters.begin() + n , wordIters.end(),
                 [](MapIt e1, MapIt e2){ return e1->second > e2->second;});
    for (auto it = wordIters.cbegin();it != wordIters.begin() + n; ++it) {
        std::printf(" %-10s%10zu\n", (*it)->first.c_str(), (*it)->second);
    }

}

class RandVar {
    public:
     RandVar() : _val(rand()) { }
     void save(ostream& os) const { os << _val << endl; }
     private:
     int _val;
};
const int NSIZE = 16;
void ex2_3(){
    ofstream out_file("output.dat");
    array<RandVar,NSIZE> rands;
    /*
     TODO: apply std::for_each on rands to save all its elements
     */
    for_each(rands.begin(), rands.end(), [&out_file](RandVar rvar){rvar.save(out_file);});
}

#endif //PRACTICE_EX2_H
