from pyspark import SparkContext
from pyspark.sql import SparkSession
from pyspark.sql.functions import udf

sc = SparkContext()
ss = SparkSession(sc)

names_rdd = sc.parallelize([
    "Braund, Mr. Owen",
    "Cumings, Mrs. Giovanna",
    "Allen, Mr. William",
    "Moran, Mr. James",
    "Nasser, Mrs. Nicht",
    "Allen, Mrs. Anna",
    "Allen, Mr. Boris",
    "Cumings, Mr. Albert",
    "Palson, Master Nick",
    "Moran, Prof. Henry"
]).map(lambda x: (x, ))

names_df = names_rdd.toDF(["name"])

names_df.show()

get_cognome = udf(lambda x: x.split(',')[0])

family_names_df = names_df.select(get_cognome(names_df.name)).withColumnRenamed("<lambda>(name)", "family_name")

family_names_df.groupBy("family_name").count().show()