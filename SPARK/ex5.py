# Relying on the RDD API, implement the following query:
# Provide the name of Portuguese players.
# Relying on the DataFrame API, implement the following query:
# Identify the players (name, nation, and number) who won at least one game.

from collections import namedtuple
from pyspark import SparkContext
from pyspark.sql import SparkSession

team = namedtuple("team", "nation Tshirt_color1 Tshirt_color2")
player = namedtuple("player", "nation number name")
game = namedtuple("game", "id team1 team2 date city score1 score2")

team1 = team("Portugal", "red", "white" )
team2 = team("Spain", "red", "white")
team3 = team("France", "white", "blue")

player1 = player("Portugal", "7", "Ronaldo")
player2 = player("Spain", "19", "Costa")
player3 = player("France", "4", "Griezmann")

game1 = game("1", "Portugal", "Spain", "15/6/2018","Moscow", 3, 4)
game2 = game("2", "France", "Australia", "16/6/2018","Kazan", 2, 1)

sc = SparkContext()
ss = SparkSession(sc)

teamsRDD = sc.parallelize([team1,team2,team3])
playersRDD = sc.parallelize([player1,player2, player3])
gamesRDD = sc.parallelize([game1,game2])

teamsDF = teamsRDD.toDF(["nation", "Tshirt_color1", "Tshirt_color2"])
playersDF = playersRDD.toDF(["nation", "number", "name"])
gamesDF = gamesRDD.toDF(["id", "team1", "team2", "date", "city", "score1", "score2"])

# Solution
names = playersRDD.filter(lambda x : x[0] == "Spain").map(lambda x: x[2]).collect()
print(names)

team1DF = gamesDF.filter("score1 > score2").select("team1")
team2DF = gamesDF.filter("score1 < score2").select("team2")

team1DF.show()
team2DF.show()

winnerTeamsDF = team1DF.union(team2DF).withColumnRenamed("team1", "winner_team")

playersDF.show()
playersDF.join(winnerTeamsDF, playersDF.nation == winnerTeamsDF.winner_team).select("name", "nation", "number").show()

