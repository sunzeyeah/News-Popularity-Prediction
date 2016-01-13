#Title segmentation
import jieba
import csv
csv.field_size_limit(1000000000)
jieba.enable_parallel(20)

content = csv.reader(open('/media/sunzeyeah/Personal/SENIOR/Thesis/Data/Chinese/Sina/news_8.csv','r'))
f = open('/media/sunzeyeah/Personal/SENIOR/Thesis/Data/Chinese/Sina/edu.csv','w')
#csvfile = open('/media/sunzeyeah/Personal/SENIOR/Thesis/Data/Chinese/title.txt','w')
writer = csv.writer(f)
for line in content:
 if line[2] != 'title':
  words = ' '.join(jieba.cut(line[2]))
# string = words + '\n'
  writer.writerow([words.encode('utf-8')])
#  f.write(string.encode('utf-8'))
