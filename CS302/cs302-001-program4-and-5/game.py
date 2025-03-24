from random import *
from math import floor

#Bradley Chang CS 302 Program #4
#This file contains the core hierarchy and its member function implementation

#Base player class
class player(object):

    #Constructor for base data
    def __init__(self, name, health, damage, potions, sword, armor):
        self._name = name
        self._health = health
        self._damage = damage
        self._potions = potions
        self._sword = sword
        self._armor = armor

    def insert_name(self):
        #print("Insert your name: ")
        self._name = input("Insert your name")
        print("Your name is", self._name)
        return 1

    def display(self):
        print("---Player stats---")
        print("Health: ")
        print(self._health)
        print("Damage: ")
        print(self._damage)
        print("Potions: ") 
        print(self._potions)
        print("Armor: ")
        print(self._armor)
        return 1

#Decision 
class decision(player):

    #Constructor for decision
    def __init__(self, name, health, damage, potions, sword, armor):
        super().__init__(name, health, damage, potions, sword, armor)
        #self._event = "None"

    #Member functions
    def random_event(self):     #Uses random to call a random event.
        num = floor(random() * 10)
        if(num < 5):
            self.trapped_item()
            return num
        else:
            self.save_NPC()
            return num

    def trapped_item(self):
        print("You encounter a trapped sword!")
        print("Do you take it? (Type yes or no)")
        print("If you choose 'yes', then you'll take damage and gain a sword")
        print("If you choose 'no', then nothing will happen")

        choice = input()
        if(choice.upper() == 'YES'):
            print("You've picked up a sword!\nBut you got scathed by a spike! -5 health")
            self._health -= 5
            return 1
        else:
            print("You decided to ignore the sword and move along")
            return 2
            

    def save_NPC(self):
        print("You encoutered an injured Wizard!")
        print("Wizard: 'Hello there traveller! I've been injured by a monster. Could you lend a hand?' ")
        print("Help out the wizard? (Type yes or no)")
        print("If you choose 'yes', you'll use a health potion to heal him")
        print("If you choose 'no', then you'll move on")

        choice = input()
        if(choice.upper() == 'YES' and self._potions >= 1):
            print("You helped the wizard! -1 health potion")
            print("He thanks you and gives you some armor. +20 armor")
            self._potions -= 1
            self._armor += 20
            return 1
        else:
            print("You decide to ignore the wizard and move on")
            return 2


#Repition Derived class
class repetition(player):
    #Constructor for repetition
    def __init__(self, name, health, damage, potions, sword, armor):
        super().__init__(name, health, damage, potions, sword, armor)
        self._m_health = 0
        self._m_damage = 0
        self._m_name = " "
    
    #Member functions
    def random_monster(self):   #Uses random to call a random monster encounter
        num = floor(random() * 10)
        if(num < 5):
            self.slime_fight()
        else:
            self.zombie_fight()
    
    def display(self):          #Displays the monster's stats
        print("---Monster stats---")
        print("Name: ")
        print(self._m_name)
        print("Health: ")
        print(self._m_health)
        print("Damage: ")
        print(self._m_damage)
        return 1

    
    def slime_fight(self):      #A slime fight that the player can encounter
        self._m_health = 30
        self._m_damage = 5
        self._m_name = "Slime"
        print("You've encountered a slime!")
        while(self._m_health > 0 and self._health > 0):
            super().display()
            self.display()
            print("You attacked the slime! Damage dealt: ")
            print(self._damage)
            print("The slime attacked you! Damage dealt: ")
            print(self._m_damage)
            self._m_health -= self._damage
            self._health -= self._m_damage
            input("Press ENTER to continue")

        if(self._m_health <= 0):
            print("You've defeated the slime!")
            return 1
        else:
            print("You adventure has come to an end!")
            return 2


    def zombie_fight(self):
        pass


#Actions derived class
class statement(player):
    
    #Constructor for statement
    def __init__(self, name, health, damage, potions, sword, armor):
        super().__init__(name, health, damage, potions, sword, armor)
    
    #Member functions
    def use_potion(self):
        if (self._potions >= 1):
            print("You used a potion!")
            print("+20 health")
            self._potions -= 1
            self._health += 20
            if(self._health > 100):
                self._health = 100
            return 1
        else:
            print("You don't have any potions to use!")
            return 2
    def narration(self):
        pass

