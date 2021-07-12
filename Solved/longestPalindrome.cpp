class Solution {
public:
    
    bool checkPalindrome(std::string_view s,bool* pIsAllRepeating=nullptr)
    {
        auto middle = s.size()/2;
        bool isAllRepeating = true;
        //assume odd
        for(int i=0;i<middle;++i)
        {
            if(s[i]!=s[s.size()-1-i])
                return false;
            if(s[i]!=s[0])
                isAllRepeating = false;
        }
        if(s[0]!=s[middle]) isAllRepeating = false;
        if(pIsAllRepeating)
            *pIsAllRepeating = isAllRepeating;
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
    std::string_view dumbSolution2(std::string_view s)
    {
        //printf("start %s\n", s.data());
        std::string_view result = s.substr(0,1);
        for(size_t i=0;i<s.size();++i)
        {
            auto subSize =s.size()-i;
            for(size_t j=result.size()+1;j+i<=s.size();++j)
            {
                auto substr = s.substr(i,j);
                auto tmp = std::string(substr);
                //printf("substr %s\n",tmp.c_str());
                bool isAllRepeating=false;
                if(checkPalindrome(substr,&isAllRepeating))
                {
                    result =substr;
                    if(!isAllRepeating)
                    {
                        //If it's a palindrome that is non repeating,
                        // the next possible palindrome is 2n -1 aba -> ababa baab -> baabaab
                        j+= j-1;  
                        //subtract one to account for loop increment
                        j--;
                    }else
                    {
                        //if it's repeating, keep going until we break the repeating combo
                        while(i+j<s.size() && s[i] == s[i+j])
                        {
                            ++j;
                        }
                        result = s.substr(i,j);
                    }
                }
            }
        }
        return result;
    }
    
    string longestPalindrome(string s) {
     return std::string{dumbSolution2(s)};   
    }
};