//This contains two approaches: First method being the intuitive, but slow version.
//Second being an optimization that dealt with the core problem of why the first
//approach was slow: Insertion
//The second approach required a bit of googling to get the idea.
//The tree diagram here helped a lot: https://aakinshin.net/posts/partitioning-heaps-quantile-estimator/
class MedianFinder {
public:
    /** initialize your data structure here. */
    struct DumbMethod
    {
		using container_t = vector<int>;
        container_t  values;
        
		void shift(container_t::iterator begin, container_t::iterator end)
		{
			for(auto itr = end; itr-->begin;)
			{
				*(itr+1) = *(itr);
			}
		}
		
        void addNum(int num)
        {
            //Add space (don't call resize because that may mess with grow)
            values.emplace_back(0);
            auto blank =values.end()-1;
            auto insertionSpot = values.size()<2?values.begin():std::lower_bound(values.begin(),blank,num);
            if(values.size()>1)
            {
			//printf("shifting %d\n",*insertionSpot);
			    shift(insertionSpot,blank);
            }
			//printf("adding %d\n",num);
			*insertionSpot = num;
			
        }
        void printValues()const
        {
            printf("arr:");
            for(auto v : values)
            {
                printf("%d,",v);
            }
            printf("\n");
        }
		double findMedian()const
		{
			if(values.size()%2)
				return values[values.size()/2];
			else
				return values[values.size()/2]/2.0 + values[(values.size()/2)-1]/2.0;
		}
    };
    struct HardleSteiger
    {
		template<typename T,typename Operator>
		struct Heap
		{
		vector<T> heap;
		Operator compare;
		void add(T val)
		{
			heap.emplace_back(val);
			std::push_heap(heap.begin(),heap.end(),compare);
		}
		T pop()
		{
			std::pop_heap(heap.begin(),heap.end(),compare);
			auto result = heap.back();
			heap.pop_back();
			return result;
		}
		T head()const
		{
			return heap.front();
		}
		size_t size()const{ return heap.size();}
		};
        //Max heap stores the smaller values
        Heap<int,std::less<int>> maxHeap;
        //Min heap stores the larger values
        Heap<int,std::greater<int>> minHeap;
		double median=0;
		
		size_t listSize ()
		{
			return maxHeap.size()+minHeap.size();
		}

		void addNum(int num) {
			
            if(listSize() ==0)
            {
                maxHeap.add(num);
                return;
            }
            
			if(num<maxHeap.head())
			{
				maxHeap.add(num);
			}else 
			{
				minHeap.add(num);
			}
			balance();
		}
		void balance()
		{
			ptrdiff_t diff=maxHeap.size();
			diff -= minHeap.size();
			//Too many elements in one of the heaps
			while(abs(diff)>1)
			{			
				//too many elements in maxHeap
				if((minHeap.size()+1)<maxHeap.size())
				{
					minHeap.add(maxHeap.pop());
				}else{
					maxHeap.add(minHeap.pop());	
				}
                diff=maxHeap.size();
			    diff -= minHeap.size();
			}
				//computeMedian();
		}
		void computeMedian()
		{
			if(listSize()%2)
			{
				if(minHeap.size()<maxHeap.size())
				{
					median = maxHeap.head();
				}else{
					median = minHeap.head();
				}
			}else{
				median = maxHeap.head()/2.0 + minHeap.head()/2.0;
			}
		}
        void printHeaps()
        {
            printf("Max Heap:\n");
            for(auto v: maxHeap.heap)
                printf("%d,",v);
            printf("\nMin Heap:\n");
            for(auto v: minHeap.heap)
                printf("%d,",v);
            
            printf("\n");
        }
		
		double findMedian() {
           // printHeaps();
				computeMedian();
			return median;
		}
    };
    DumbMethod dm;
    HardleSteiger hs;
    MedianFinder() {
        
    }
    
    
    void addNum(int num) {
        hs.addNum(num);
    }
    
    double findMedian() {
        return hs.findMedian();
    }
};

/**
 * Your MedianFinder object will be instantiated and called as such:
 * MedianFinder* obj = new MedianFinder();
 * obj->addNum(num);
 * double param_2 = obj->findMedian();
 */