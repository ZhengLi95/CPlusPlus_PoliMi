from pyspark import SparkContext

sc = SparkContext("local", "Zheng's APP")
print('\n\n\n')

lines = sc.textFile("hamlet.txt")

print(lines.collect())

counts = lines.flatMap(lambda x: x.split(' '))\
    .map(lambda x: (x, 1))\
    .reduceByKey(lambda x, y: x + y)
output = counts.collect()

for (word, count) in output:
    print("%s: %i" % (word, count))