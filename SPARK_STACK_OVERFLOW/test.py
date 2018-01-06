
import collections
from pyspark import SparkContext, SparkConf

conf = SparkConf()
conf.setMaster("local").setAppName("My app")

sc = SparkContext("local", "My App")

Question = collections.namedtuple("Question", "id id_user title text keywords views votes")
Answer = collections.namedtuple("Answer", "id id_question id_user text")
User = collections.namedtuple("User", "id reputation profile")

q1 = Question(1, 1, "Cassandra Upsert not working on conditional writes", 
    "I made a conditional insert (if not exists) statement using DataStax java driver but it doesn't work", 
    "Java Cassandra DataStax", 1, 0)
q2 = Question(2, 1, "New Spark 2.2 Cassandra Connector", 
    "Tried to run the new connector to Spark 2.2 got error code 99129 who can be of help?", 
    "Spark Cassandra", 2, 3)

u1 = User(1, 1, "I'm an indipendent programmer, 8 years expertise in Java dev")
u2 = User(2, 5, "I'm Matei, Spark creator")
u3 = User(3, 5, "I'm Guido, Python benevolent dictator")

a1 = Answer(1, 1, 2, "I think there is still a problem in DataStax connector, try to use the one at this link XXX")
a2 = Answer(2, 2, 2, "Did you check server IP and Scala version?")
a3 = Answer(3, 2, 3, "I think you are using Python 2.7, while the new API is for Python 3.0")

questionsRDD = sc.parallelize([q1,q2])
usersRDD = sc.parallelize([u1,u2,u3])
answersRDD = sc.parallelize([a1,a2,a3])

print("sorry!")