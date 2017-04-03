def binarySearch(list,val):
    if(len(list) > 0):
        mid = len(list)//2
        if(list[mid] == val):
            return True
        elif(val < list[mid]):
            start = 0
            end = mid
        else:
            start = mid + 1
            end = len(list)
            
        return binarySearch(list[start:end],val)
    return False