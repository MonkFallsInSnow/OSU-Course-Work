import random
import time

def itrMinMax(list):
    min = list[0];
    max = list[0];

    for element in list:
        if(min > element):
            min = element;
        if(max < element):
            max = element;

    dict = {'Min': min, 'Max': max};
    return dict;

#tuple(min,max)
def recMinMax(list):
    if(len(list) == 1):
        return (list[0], list[0])
    elif(len(list) == 2):
        if(list[0] < list[1]):
            return (list[0], list[1])
        else:
            return (list[1], list[0])

    t1 = recMinMax(list[0:(int)(len(list)/2)])
    t2 = recMinMax(list[(int)(len(list)/2):len(list)])
    return compare(t1,t2)  

def compare(t1,t2):
    min = t1[0]
    max = t1[1]

    if(t1[0] > t2[0]):
        min = t2[0]

    if(t1[1] < t2[1]):
        max = t2[1]

    return (min,max)


aList = []

for x in range(1,9000000):
    aList.append(random.randint(1,1000000))

print('starting...')
startTime = time.clock()
print("iterative: ",itrMinMax(aList))
print("time: ", time.clock() - startTime)
startTime = time.clock()
print("recursive: ",recMinMax(aList))
print("time: ", time.clock() - startTime)


