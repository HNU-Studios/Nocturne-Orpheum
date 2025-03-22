#include "sectors.h" // only included so that includes in main wouldn't break by including item here
vector<item> Weapons = {item("Sword of the Sun God", "Weapon", 25, true), item("Sword of the Moon God", "Weapon", 25, true)};
vector<item> Gear = {item("Breastplate of the Sun God", "Breastplate", 8), item("The Sun God's Helmet", "Helmet", 5), item("Gloves of the Sun God", "Gloves", 3), item("Mask of the Sun God", "Mask", 1), item("Breastplate of the Moon God", "Breastplate", 8), item("The Moon God's Helmet", "Helmet", 5), item("Gloves of the Moon God", "Gloves", 3), item("Mask of the Moon God", "Mask", 1)};
vector<item> Specials = {item("Instakill", "Special", 0), item("Revival", "Special", 0)};
void shop(){
    char op;
    cout << "Enter a category to purchase an item from:\nFor weapons: w\n For gear: g\nFor special items: s" << endl;
    cin >> op;
    op = tolower(op);
    int count = 1;
    if (op == 'w'){
        for (item i: Weapons){
            cout << count << ") " << i.getName() << ": " << i.getPower() << " gold" << endl;
            count++;
        }
    }
    if (op == 'g'){
        for (item i: Gear){
            cout << count << ") " << i.getName() << ": " << i.getPower() << " gold" << endl;
            count++;
        }
    }
    if (op == 's'){
        for (item i: Specials){
            cout << count << ") " << i.getName() << ": " << i.getPower() << " gold" << endl;
            count++;
        }
    }
    else{
        cout << "Invalid input, please try again." << endl;
        return;
    }
    cout << "Enter the number of the item to purchase: ";
    long unsigned int i;
    cin >> i;
    if (op == 'w'){
        if (i - 1 < Weapons.size()){
            if (misc[item("Gold", "Misc", 1)] > Weapons[i - 1].getPower()){
                misc[item("Gold", "Misc", 1)]--;
                weapons[Weapons[i - 1]]++;
            }
        }
    }
    if (op == 'g'){
        if (i - 1 < Gear.size()){
            if (misc[item("Gold", "Misc", 1)] > Gear[i - 1].getPower()){
                misc[item("Gold", "Misc", 1)]--;
                gear[Gear[i - 1]]++;
            }
        }
    }
    if (op == 's'){
        if (i - 1 < Specials.size()){
            if (misc[item("Gold", "Misc", 1)] > Gear[i - 1].getPower()){
                misc[item("Gold", "Misc", 1)]--;
                misc[Specials[i - 1]]++;
            }
        }
    }
}
