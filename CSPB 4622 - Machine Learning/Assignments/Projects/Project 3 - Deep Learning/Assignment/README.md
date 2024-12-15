# Project 3 Guideline

1. Identify a deep learning problem. 
- Regarding dataset from a kaggle competition or similar, you must provide more focus on model building and/or analysis to be a valid project (replicating what's in the kaggle kernel or other notebooks available online is not a valid project. You must implement other approaches and compare with those).
- If you have a relationship with a company or organization who are willing to provide a project task or data, you're welcome to work on their problem (In this case, you might not need to share the data). 
- If you find a research paper, you can replicate the experiments and implement your improved algorithm.
2. Gather data: The data can be web-scraped, or downloaded from any sources as long as it's legal and ethical, and does not violate their policy or intellectual property/copyrights.
3. Clean the data, do EDA (exploratory data analysis- e.g., inspecting and visualization of the data)
4. Perform analysis using machine learning models of your choice. If your project involves making an webapp (not required), you can include the demo.
5. Deliver the results: These deliverables serves two purposes - grade for this course and your project portfolio that you can show when you apply for jobs in the near futures.

**[Deliverables]** 
1. GitHub repo commits: Jupyter notebook showing a brief problem description, EDA procedure, analysis (model building and training), result and discussion/conclusion. If your work becomes large that it doesn't fit into one notebook (or you think it will be less readable by having one large notebook), you can make several notebooks or scripts in this git
2. Moodle submission for feedback: a report-style notebook or pdf - with your name and the link to your project github repo. Also, in case your project doesn't fit into jupyter notebook format (e.g. you built an app that uses ML), write your approach as a report and submit in a pdf form.
3. Follow the provided rubric closely to complete all required tasks. We will enforce a more strict grading than Project 1.

**[Optional]** You may choose to include short summary or recorded presentation or anything that you want to include/demonstrate. Be sure to be concise and clear. This optional step can be used as building your portfolio.

Here are the rough steps:         

1. **Step 1:** In the earlier phase, you were to make the initial selection of a data source and problem. In this stage, you're going to go through the initial data cleaning and EDA, and judge whether you need to collect more data or different data etc. Feel free to share and discuss your idea in the class discussion board.

2. **Step 2:** Continue more EDA if needed. Start the main analysis and build your deep learning models. Depending on your tasks, you may have one model or more. Generally, it is deemed to be a higher quality project if you compare multiple models and show your understanding of why certain model works better than others or what limitations or cautions certain models may have (especially for deep learning models, show enough effort on the hyperparameter optimization).

3. **Step 3:** Continue more main analysis. Hyperparameter optimization. Compare results from your models. Wrap up.

4. **Step 4:** Wrap up and finalize your jupyter notebook write-up. (Optional: Prepare the presentation. Organize your git repository.) Submit the deliverables.

### Defining project idea
The purpose of this project is to apply the skills you learned from our 2nd and 3rd parts. Therefore, choose a topic and data that are suitable for the methods/models we learned in each part. 

Your project will focus on deep learning tasks (image/text/video/sound classification, image segmentation, image/text generation, deep learning on multimodal data, etc.)

**Same reminder from project 1:** We recommend finding data from ML competition or data repositories rather than scraping from the web or multiple sources yourself. Using well-organized data will save you time as we have shorter (and more frequent) timelines for mini-projects than the usual final project you may have seen in other classes. You can think of a mini project as a simpler project (that you can work in 1-2 weeks part-time). So we recommend not to choose something too ambitious. But if you have time and interest, you're welcome to challenge yourself.

### EDA procedure example (Steps 1-2)
- Describe the data sources, the hypothesis or problem you which to analyze and then describe the factors or components that make up the dataset (The "factors" here is called "features" in the machine learning term. These factors are often columns in the tabulated data). For each factor, use a box-plot, scatter plot, histogram etc to describe the distribution of the data as appropriate.
- Describe correlations between different factors of the dataset and justify your assumption that they are correlated or not correlated. You may use numeric or qualitative / graphical analysis for this step.
- Determine if any data needs to be transformed.
- Using your hypothesis, indicate if it's likely that you should transform data, such as using a log transform or other transformation of the dataset.
- You should determine if your data has outliers or needs to be cleaned in any way. Are there missing data values for specific factors? How will you handle the data cleaning? Will you discard, interpolate or otherwise substitute data values?
- If you believe that specific factors will be more important than others in your analysis, you should mention which and why. You will use this to confirm your intuitions in your final writeup.

### How to find data
There are a plethora of data resource these days. Here are a few popular (classic ML data) ones.     
- [UCI ML data repository](https://archive.ics.uci.edu/ml/datasets.php): Their data is from researchers mostly and is relatively clean. Also the task types are mostly for classification or regression, therefore many of them are suitable for the scope of this course's project.     
- [Kaggle](https://www.kaggle.com/): Perhaps one of the most popular data science/ML data repositories today, they have many interesting con-going or past competitions. But most of recent dataset/tasks will be beyond the scope of this course. Should you be still interested, choose problems that have tabulated data and classification or regression type tasks.     
- [Data.gov](https://www.data.gov/) has many government sources of data. You can filter for a specific topic (e.g. Finance) and then restrict your attention to e.g. CSV data, which should be easier to process.
- [Grand Challenge](https://grand-challenge.org/) has various biomed image computer vision competitions.

Some internet blogs about list of dataset:     
- https://medium.com/towards-artificial-intelligence/the-50-best-public-datasets-for-machine-learning-d80e9f030279
- https://towardsdatascience.com/top-sources-for-machine-learning-datasets-bb6d0dc3378b
- https://en.wikipedia.org/wiki/List_of_datasets_for_machine-learning_research
- http://www.statsmodels.org/devel/datasets/index.html
- https://pathmind.com/wiki/open-datasets
