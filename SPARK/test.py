import collections
from operator import add
from pyspark import SparkContext

sc = SparkContext()

Patient = collections.namedtuple("Patient", "id name address phone_number")
BloodTest = collections.namedtuple("BloodTest", "id id_patient code date description result")

patient1=Patient(1, "Alice", "Pza L. Da Vinci 32", "02 2399")
patient2=Patient(2, "Bob", "Via Golgi 40", "02 23992")

bloodTest1=BloodTest(1,1,1,"17/2/2017","Cholesterol",140)
bloodTest2=BloodTest(2,1,2,"17/2/2017","Glucose",83)
bloodTest3=BloodTest(3,2,1,"16/2/2017","Cholesterol",238)
bloodTest4=BloodTest(4,2,2,"16/2/2017","Glucose",94)

patientsRDD=sc.parallelize([patient1,patient2])
testsRDD=sc.parallelize([bloodTest1,bloodTest2,bloodTest3,bloodTest4])

a = testsRDD.filter(lambda x : x.description == "Cholesterol" and x.result >= 220)\
    .map(lambda x : (x.id_patient, x.result))

b = patientsRDD.map(lambda x : (x.id, (x.name, x.address))).join(a)\
    .map(lambda x: (x[1][0][0], x[1][0][1], x[1][1])).collect()

for elem in b:
    print("Name: %s, Address: %s, Result: %s" % elem)