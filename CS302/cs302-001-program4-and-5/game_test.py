#Bradley Chang CS302 Program 4
#This is the test suite to test out my game functions to see if they are working as expected
#Please run this test suite with python -s since this is testing some I/O functions
import pytest
from game import *

#Player base class tests
def test_player_init():
    a_player = player("bob", 100, 10, 3, 0, 0)
    assert(a_player._name == "bob")
    assert(a_player._health == 100)
    assert(a_player._damage == 10)
    assert(a_player._potions == 3)
    assert(a_player._sword == 0)
    assert(a_player._armor == 0)

def test_player_display():
    a_player = player("bob", 100, 10, 3, 0, 0)
    assert(a_player.display() == 1)

#Decision derived class test
def test_decision_init():
    a_decision = decision("Rob", 100, 10, 3, 0, 0)
    assert(a_decision._name == "Rob")
    assert(a_decision._health == 100)
    assert(a_decision._damage == 10)
    assert(a_decision._potions == 3)
    assert(a_decision._sword == 0)
    assert(a_decision._armor == 0)

def test_trapped_item():                         #Testing for trapped item function. Run with "pytest -s" to do IO
    a_decision = decision("Rob", 100, 10, 3, 0, 0)
    choice = a_decision.trapped_item()
    assert(choice == 1 or choice == 2)
    if(choice == 1):
        assert(a_decision._health == 95)

def test_save_NPC():
    a_decision = decision("Rob", 100, 10, 3, 0, 0)
    choice = a_decision.save_NPC()
    assert(choice == 1 or choice == 2)
    if(choice == 1):
        assert(a_decision._potions == 2)
        assert(a_decision._armor == 20)

#Repetition derived class test
def test_repetition_init():
    a_repetition = repetition("Cob", 100, 10, 3, 0, 0)
    assert(a_repetition._name == "Cob")
    assert(a_repetition._health == 100)
    assert(a_repetition._damage == 10)
    assert(a_repetition._potions == 3)
    assert(a_repetition._sword == 0)
    assert(a_repetition._armor == 0)
    assert(a_repetition._m_health == 0)
    assert(a_repetition._m_damage == 0)
    assert(a_repetition._m_name == " ")

def test_repetition_display():
    a_repetition = repetition("Cob", 100, 10, 3, 0, 0)
    assert(a_repetition.display() == 1)

def test_repetition_slime_fight_win():
    a_repetition = repetition("Cob", 100, 10, 3, 0, 0)
    val = a_repetition.slime_fight()
    assert(val == 1)

def test_repetition_slime_fight_lose():
    a_repetition = repetition("Cob", 10, 10, 3, 0, 0)
    val = a_repetition.slime_fight()
    assert(val == 2)

#Statement derived class test
def test_statement_init():
    a_statement = statement("Sob", 100, 10, 3, 0 , 0)
    assert(a_statement._name == "Sob")
    assert(a_statement._health == 100)
    assert(a_statement._damage == 10)
    assert(a_statement._potions == 3)
    assert(a_statement._sword == 0)
    assert(a_statement._armor == 0)

def test_statement_use_potion_success():
    a_statement = statement("Sob", 85, 10, 3, 0 , 0)
    val = a_statement.use_potion()
    assert(val == 1)
    assert(a_statement._potions == 2)
    assert(a_statement._health == 100)

def test_statement_use_potion_fail():
    a_statement = statement("Sob", 85, 10, 0, 0 , 0)
    val = a_statement.use_potion()
    assert(val == 2)
    assert(a_statement._potions == 0)
    assert(a_statement._health == 85)


