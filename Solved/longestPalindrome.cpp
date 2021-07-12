class Solution {
public:
    
    bool checkPalindrome(std::string_view s)
    {
        auto middle = s.size()/2;
        //assume odd
        for(int i=0;i<middle;++i)
        {
            if(s[i]!=s[s.size()-1-i])
                return false;
        }
        return true;
    }
    std::string_view dumbSolution(std::string_view s)
    {
        std::string_view result{};
        for(size_t i=0;i<s.size();++i)
        {
            auto subSize =s.size()-i;
            for(size_t j=0;j<subSize;++j)
            {
                auto substr = s.substr(i,subSize-j);
                if(substr.size()<=result.size())
                    break;
                if(checkPalindrome(substr))
                    result =substr;
            }
        }
        return result;
    }
    
    string longestPalindrome(string s) {
     return std::string{dumbSolution(s)};   
    }
};