import pandas as pd
import os

class Gobbler:
    def get_script_path(self):
        return os.path.dirname(os.path.realpath(__file__))

    def __init__(self):
        data_path = os.path.join(self.get_script_path(), "data.csv")
        data = pd.read_csv(data_path)
        #print(type(data)) #pandas dataFrame
        #print(type(data.values)) #numpy ndarray
        self.mArray = data.values;

    def get_data(self, idx):
        row = self.mArray[idx,:]
        rowstr = ""
        for val in row:
            rowstr = rowstr + str(val)
            rowstr += ":"
        return rowstr


# test Gobbler
#g = Gobbler()
#print(g.get_data(0))
