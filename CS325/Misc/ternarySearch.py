def ternarySearch(list,val,start,end): 

    if(start < end):
        mid1 = (2*start + end) // 3
        mid2 = (start + 2*end) // 3

        if(val < list[mid1]):
            return ternarySearch(list,val,start,mid1)
        elif(val > list[mid1] and val < list[mid2]):
            return ternarySearch(list,val,mid1,mid2)
        elif(val > list[mid2]):
            return ternarySearch(list,val,mid2+1,end)
        else:
            return True

    return False
	