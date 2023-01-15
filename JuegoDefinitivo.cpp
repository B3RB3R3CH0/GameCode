#include <iostream>
#include <stdlib.h>
#include <ctime>
#include <Windows.h>
#include <mmsystem.h>

using namespace std;

//Atributos Enemy 1
string enemyName1 = "Jorge";
int enemyHP1 = 200;
bool enemyIsAlive1 = true;

//Atributos Enemy 2
string enemyName2 = "Ramon";
int enemyHP2 = 200;
bool enemyIsAlive2 = true;

//Atributos Hero
string heroName;
int heroHP = 1000;
bool heroIsAlive = true;

//Attacks
int Placaje = 50;
int Navajazo = 80;
int Destruccion = 500;

//Limit Attack
int limitDestruccion = 1;

//Variables In Game
int enemyNum;
int damage;
int enemyChoosed;
int heroDamage;
int ataque;

void gameStart() {
    cout << "" << enemyName1 << " acaba de aparecer y tiene " << enemyHP1 << " puntos de vida\n";
    cout << "" << enemyName2 << " acaba de aparecer y tiene " << enemyHP2 << " puntos de vida\n";
    cout << "Como se llama el heroe?\n";
    cin >> heroName;
    cout << "El nombre del heroe es " << heroName << "\n";
}

void checkEnemyStatus(int& enemyHP, string enemyName, bool& enemyIsAlive) {
    if (enemyHP <= 0) {
        cout << "Te has cargado al enemigo " << enemyName << " \n";
        enemyHP = 0;
        enemyIsAlive = false;
    }
    else {
        cout << "El enemigo " << enemyName << " tiene " << enemyHP << " puntos de vida\n";
        enemyIsAlive = true;
    }
}

void chooseEnemy() {
    int enemyChoose = 0;
    while (enemyChoose != 1 && enemyChoose != 2) {
        cout << "A que enemigo quieres atacar? \n";
        if (enemyIsAlive1) {
            cout << "1.- " << enemyName1 << "\n";
        }
        if (enemyIsAlive2) {
            cout << "2.- " << enemyName2 << "\n";
        }
        cin >> enemyChoose;
        if (enemyChoose <= 0 || enemyChoose > 2) {
            cout << "La opcion elegida no es correcta. Por favor, elige una opcion valida. \n";
        }
        if (!enemyIsAlive1 && enemyChoose == 1) {
            cout << "El enemigo " << enemyName1 << " ya esta muerto. Por favor, elige un enemigo que todavia este vivo." " \n";
            enemyChoose = 0;
        }
        if (!enemyIsAlive2 && enemyChoose == 2) {
            cout << "El enemigo " << enemyName2 << " ya esta muerto. Por favor, elige un enemigo que todavia este vivo." " \n";
            enemyChoose = 0;
        }
    }
    enemyChoosed = enemyChoose;
}

void chooseAttack() {
    int attackChoose = 0;
    while (attackChoose != 1 && attackChoose != 2 && attackChoose != 3) {
        cout << "Que ataque quieres usar? \n";
        cout << "1.- Placaje \n";
        cout << "2.- Navajazo \n";
        if (limitDestruccion > 0) {
            cout << "3.- Destruccion\n";
        }
        cin >> attackChoose;
        if (attackChoose <= 0 || attackChoose > 3) {
            cout << "El ataque seleccionado no es correcto. Por favor, elige una opcion valida. \n";
        }
        if (attackChoose == 3) {
            if (limitDestruccion > 0) {
                limitDestruccion--;
            }
            else {
                attackChoose = 0;
                cout << "No te queda magia. Por favor selecciona un ataque que puedas usar. \n";
            }
        }
    }
    if (attackChoose == 1) {
        heroDamage = Placaje;
    }
    else if (attackChoose == 2) {
        heroDamage = Navajazo;
    }
    else {
        heroDamage = Destruccion;
    }
}

void heroAttackEnemy(int damage, string enemyName, int& enemyHP) {
    cout << "Atacas al enemigo " << enemyName << " y le haces " << damage << " de dano \n";
    enemyHP = enemyHP - damage;
}

void enemyAttack(int damage, string enemyName) {
    heroHP = heroHP - damage;
    if (heroHP > 0) {
        cout << "El enemigo " << enemyName << " te ha atacado y te quedan " << heroHP << " puntos de vida\n";
    }
    else {
        cout << "El enemigo " << enemyName << " te ha atacado y te ha matado. El mundo esta condenado. \n";
        heroIsAlive = false;
    }
}


int main()
{
    gameStart();
    while (heroIsAlive && (enemyIsAlive1 || enemyIsAlive2)) {
        //ELEGIMOS ENEMIGO AL QUE ATACAR
        chooseEnemy();
        //ELEGIMOS ATAQUE Y CAPTURAMOS EL VALOR DEL DANYO QUE HAREMOS
        chooseAttack();

        if (enemyChoosed == 1) {
            //ATACAMOS AL ENEMIGO 1
            heroAttackEnemy(heroDamage, enemyName1, enemyHP1);
            checkEnemyStatus(enemyHP1, enemyName1, enemyIsAlive1);
        }
        else {
            //ATACAMOS AL ENEMIGO 2
            heroAttackEnemy(heroDamage, enemyName2, enemyHP2);
            checkEnemyStatus(enemyHP2, enemyName2, enemyIsAlive2);
        }
        //ATACA EL ENEMIGO 1 SI ESTÁ VIVO Y EL HÉROE TAMBIÉN
        if (enemyIsAlive1 && heroIsAlive) {
            enemyAttack((30 + rand() % 20), enemyName1);
        }
        //ATACA EL ENEMIGO 2 SI ESTÁ VIVO Y EL HÉROE TAMBIÉN
        if (enemyIsAlive2 && heroIsAlive) {
            enemyAttack((30 + rand() % 20), enemyName2);
        }
    }
}