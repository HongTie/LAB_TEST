import json 

def is_dev(x):          # a function to do filtering at line 14.
    if x['role'] =="developer":
        return x

try:
    f = open('data.json')             # read the .json file.        
    data = json.load(f)
except:                               # error opening .json file.
    print("Failed opening 'data.json'.")    
f.close()

newlist = list(filter(is_dev,data['user']))     # identify the developers and put in newlist.

print('developers:')    # output the developer's list.
for j in newlist:
    print(j['name'])





