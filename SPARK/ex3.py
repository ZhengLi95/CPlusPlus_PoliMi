from collections import namedtuple
from operator import add
from pyspark import SparkContext

sc = SparkContext()

driver = namedtuple("driver", ["id", "name", "surname"])
taxi = namedtuple("driver", ["number", "name", "driver"])
receipt = namedtuple("receipt", ["number", "from_addr", "to_addr", "taxi" , "price"])
driver1 = driver(1, "Peter", "Parker")
driver2 = driver(2, "Clark", "Kent")
driver3 = driver(3, "Diana", "Prince")

taxi1 = taxi(1, "Spiderman", 1)
taxi2 = taxi(2, "Superman", 2)
taxi3 = taxi(3, "Wonder Woman", 3)

receipt1 = (1,"Chappaqua road", "Main street", 1, 100)
receipt2 = (2,"Broadway", "Main street", 1, 150)
receipt3 = (3,"Kitchawan road", "Broadway", 2, 250)
receipt4 = (4,"Broadway","Kitchawan road", 3, 180)

driversRDD = sc.parallelize([driver1, driver2, driver3])
taxisRDD = sc.parallelize([taxi1,taxi2,taxi3])
receiptsRDD = sc.parallelize([receipt1, receipt2, receipt3, receipt4])


cartesian_receiptsRDD = receiptsRDD.cartesian(receiptsRDD)

two_way_ridesRDD = cartesian_receiptsRDD.filter(lambda x: x[0][1] == x[1][2] and x[0][2] == x[1][1])

two_way_ridesRDD.collect()

two_way_rides_prices_RDD = two_way_ridesRDD.flatMap(lambda x: [x[0][-1], x[1][-1]])
print two_way_rides_prices_RDD.collect()
print 0.5*two_way_rides_prices_RDD.reduce(add)