library(NLP)
library(tm)
segmentCN = readLines("F:\\SENIOR\\Thesis\\Data\\Chinese\\stopwordsCN.txt")
mydata = read.csv("F:\\SENIOR\\Thesis\\Data\\Chinese\\title_splitted_gbk.csv")
sport = Corpus(VectorSource(mydata))
sport = tm_map(sport,removeNumbers)
sport = tm_map(sport,removePunctuation)
sport = tm_map(sport,removeWords,segmentCN)
len = length(sport[[1]]$content)
string = c()
for(i in 1:len){
string = c(string,sport[[1]]$content[i])
}
write.csv(string,"F:\\SENIOR\\Thesis\\Data\\Chinese\\title_cleaned.csv",row.names=F,col.names=F)
