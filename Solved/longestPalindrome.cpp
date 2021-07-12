class Solution {
public:
    
    //TODO: create and use a modified version that assumes that there are no sub palindromes
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
    std::string_view checkReverse(size_t palindromeOffset,size_t offset,std::string_view palindrome, std::string_view theRest)
    {
        auto result = theRest.substr(0,offset);
        bool match = false;
        do
        {
            match =false;
        if(theRest.size()>=offset-palindromeOffset+palindrome.size())
        {
            match = true;
            for(size_t i=palindromeOffset,j=offset; i<palindrome.size() ;++i,++j)
            {
                 if(palindrome[i] != theRest[j])
                 {
                     match = false;
                     break;
                 }
            }
            if(match) result = theRest.substr(0,offset+palindrome.size()-palindromeOffset);
            //auto rstr = std::string(result);
            offset=result.size();
        }
        }while(match);
        return result;
    }
    std::string_view exploreMirror(std::string_view palindrome, std::string_view theRest,bool isAllRepeating)
    {
        std::string_view result=palindrome;
        auto offset = palindrome.size();
        auto augmentedP = palindrome;
        if(isAllRepeating)
            augmentedP = palindrome.substr(0,1);
        
        //auto tmp = std::string(palindrome);
        //do
        //{       
        //    palindrome = result;
         //   tmp = palindrome;
            result = checkReverse(0,offset,augmentedP,theRest);
            if(!isAllRepeating && result.size()==palindrome.size())
                result = checkReverse(1,offset,augmentedP,theRest);
            //if we found a new palindrome, repeat with the new palindrome
        //}while(result.size()!=palindrome.size());
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
                auto fullSubstr=s.substr(i);
                auto substr = fullSubstr.substr(0,j);
                //auto tmp = std::string(substr);
                //printf("substr %s\n",tmp.c_str());
                bool isAllRepeating=false;
                if(checkPalindrome(substr,&isAllRepeating))
                {
                    //if this is a palindrome, check if the subsequent sequence is a mirrored version of this
                    result=exploreMirror(substr,fullSubstr,isAllRepeating);
                    j= result.size()*2-1; 
                    
                }
            }
        }
        return result;
    }
    
    string longestPalindrome(string s) {
     return std::move(s=dumbSolution2(s));   
    }
};