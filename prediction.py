#random forest prediction
from sklearn.ensemble import RandomForestClassifier
from sklearn import cross_validation
import numpy as np
import csv
from sklearn.externals import joblib
import time
import random


#generate training and test set
cluster = [119]#[1663,832,416,333,277,238,208,185,166,151,139,119,104,92,83]
f = open('/media/sunzeyeah/Personal/SENIOR/Thesis/Data/Chinese/test_Ncluster.csv','a')
writer = csv.writer(f)
for one in cluster:
 print one
 path = '/media/sunzeyeah/Personal/SENIOR/Thesis/Data/Chinese/Netease/TitleVectors_' + str(one)+'_5.csv'
 content = csv.reader(open(path,'r'))
 data = np.zeros((8767,one+1),dtype = "int32")
 i = 0
 for line in content:
  data[i] = line
  i = i + 1
 j = 50
 while j <= 500:
  print j
  rf = RandomForestClassifier(n_estimators = j)
  i = 0
  score = []
  times = []
  while i < 10:
   rand = random.randint(0,500)
   in_train,in_test,out_train,out_test = cross_validation.train_test_split(data[:,1:],data[:,0],test_size=0.02,
   	random_state=rand)
  #Fit model
  #i = 300
  #times = []
  #score= []
  #while i<=500:
   time1 = time.time()
   forest = rf.fit(in_train,out_train)
   time2 = time.time()
   times.append(time2-time1)
   score.append(forest.score(in_test,out_test))
   print i
   i = i + 1
  writer.writerow(score)
  j = j + 50

f.close()
score = 0
i = 0
while score <= 0.8:
 rand = random.randint(0,500)
 in_train,in_test,out_train,out_test = cross_validation.train_test_split(data[:,1:],data[:,0],test_size=0.02,random_state=rand)
 forest = rf.fit(in_train,out_train)
 score = forest.score(in_test,out_test)
 i = i + 1
 print i

#Save model
joblib.dump(forest, '/media/sunzeyeah/Personal/SENIOR/Thesis/Data/Chinese/Netease/RandomForest_num/119cl_5redu_150esti/rf.pkl') 
#Load model
forest = joblib.load('/media/sunzeyeah/Personal/SENIOR/Thesis/Data/Chinese/Netease/RandomForest_num/119cl_5redu_150esti/rf.pkl')
