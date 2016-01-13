# News-Popularity-Prediction
Step1 web scraping
- web scraping.py
Use Scrapy to scrape data(news title, date, contents, # of reviews, # of participants and first 10 reviews) from www.sina.com.cn.
Note: The code can be easily adjusted for other websites.

Step2 data preprocessing
- word segmentation.py
Because there is no space between Chinese words, segmentation is needed before any text analysis. The code uses 'jieba' to segment words.
- delete stop words.R
Delete the stop words based on a Chinese stop words reference.

Step3 text vectorization
Use the tool word2vec provided by Google (available on http://word2vec.googlecode.com/svn/trunk/) to train word vectors and form clusters.

Step4 clustering
- clustering.c
Transform titles and reviews into high-dimensional numeric vector based on clustering.

Step5 prediction
- predcition.py
Use random forest to train the classifier to predict the popularity of a certain news title.
