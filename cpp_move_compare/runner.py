import os
import subprocess

# count of objects to be inserted into the std::vector
ele_cnt = [b'1000\n', b'2500\n', b'5000\n', b'7500\n', b'10000\n', b'25000\n', b'50000\n', b'75000\n', b'100000\n', b'250000\n']
#output csv file
csv_file = open ("out.csv", 'w')

for e in ele_cnt:
    avg_lst = [0, 0, 0]
    print("running for element count " + str(e) + " ... ")
    #running for 10 times to normalize the result
    for k in range(10):
        print ("iteration " + str(k))
        # compare exe would print 3 numbers to its stdoout
        x = subprocess.Popen(["./compare"], shell=True, stdin=subprocess.PIPE, stdout=subprocess.PIPE)
        result = x.communicate(input=e)[0] #communicate accepts a bytes object as input
        #returns a bytes object. decode() returns a string back. split() converts it to list
        result_lst = result.decode().split()
        print(result_lst)
        for i in range(len(result_lst)):
            avg_lst[i] = avg_lst[i] + int(result_lst[i])
    avg_lst = [a/10.0 for a in avg_lst]
    for i in range(len(avg_lst)):
        if i == (len(avg_lst)-1):
            print (avg_lst[i], file=csv_file)
        else:
            print (str(avg_lst[i]) + ", ", end='', file=csv_file)
    print ('', file=csv_file)
csv_file.close()

