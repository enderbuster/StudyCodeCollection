import pickle
#to dump an object
class lunch:
    def __init__(self):
        self.fruit="banana"
        self.drink="pepsi"
    def get_drink(self):
        print(self.drink)
todays_lunch=lunch()
with open("todays_lunch.pickle",'wb') as file:
    pickle.dump(todays_lunch,file)
#to load an object
with open("todays_lunch.pickle",'rb') as file:
    preserved_lunch:lunch=pickle.load(file)

preserved_lunch.get_drink()