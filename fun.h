#include <iostream>
#include <string>
#include <map>
#include <vector>

using namespace std;

// Struct to store details of club members
struct Member {
    string full_name;
    string gender;
    string next_of_kin;
    string date_of_birth;
    string contact_details;
    string sub_county;
    string school_or_college;
    vector<string> games_of_interest;
    int weight;
    int height;
    string special_needs;
};

// Struct to store details of sports in the club
struct Sport {
    string name;
    string patron;
    vector<string> team_members;
    int facilitation_fee;
};

// Struct to store details of items in the store
struct Item {
    string name;
    int price;
    int stock_level;
};

// Struct to store details of items purchased
struct Purchase {
    string item_name;
    int quantity;
    int total_price;
};

// Struct to store details of facilitation fees
struct FacilitationFee {
    string sport_name;
    int fee;
    int total_fee;
};

// Struct to store details of patron's commission
struct PatronCommission {
    string sport_name;
    int commission;
    int total_commission;
};

// Struct to store details of surcharge for lost or damaged equipment
struct Surcharge {
    string item_name;
    int market_value;
    int fee;
    int total_fee;
};

// Struct to store details of total income for the club
struct TotalIncome {
    int membership_fee;
    int discounted_price;
    int total_amount_of_items_bought;
    int surcharged_fee;
    int facilitation_fee;
    int patron_commission;
    int total_income;
};

// Function to maintain details of the club members and their roles
inline void maintain_member_details(vector<Member> &members) {
    Member member;
    cout << "Enter full name: ";
    cin >> member.full_name;
    cout << "Enter gender: ";
    cin >> member.gender;
    cout << "Enter next of kin: ";
    cin >> member.next_of_kin;
    cout << "Enter date of birth: ";
    cin >> member.date_of_birth;
    cout << "Enter contact details: ";
    cin >> member.contact_details;
    cout << "Enter sub-county: ";
    cin >> member.sub_county;
    cout << "Enter school or college: ";
    cin >> member.school_or_college;
    cout << "Enter games of interest (in order of priority): ";
    string game;
    cin >> game;
    while (cin >> game) {
	        if (game == "done") { 
    		    break; 
    		}
        member.games_of_interest.push_back(game);
   }
    cout << "Enter weight: ";
    cin >> member.weight;
    cout << "Enter height: ";
    cin >> member.height;
    cout << "Enter special needs: ";
    cin >> member.special_needs;
    members.push_back(member);
}

// Function to maintain details of the sports in the club
inline void maintain_sport_details(vector<Sport> &sports) {
    Sport sport;
    cout << "Enter sport name: ";
    cin >> sport.name;
    cout << "Enter patron: ";
    cin >> sport.patron;
    cout << "Enter team members: ";
    string member;
    while (cin >> member) {
	        if (member == "done") { 
        break; 
    }
        sport.team_members.push_back(member);
    }
    cout << "Enter facilitation fee: ";
    cin >> sport.facilitation_fee;
    sports.push_back(sport);
}

// Function to maintain records of the items in the store
inline void maintain_item_details(map<string, Item> &items) {
    Item item;
    cout << "Enter item name: ";
    cin >> item.name;
    cout << "Enter price: ";
    cin >> item.price;
    cout << "Enter stock level: ";
    cin >> item.stock_level;
    items[item.name] = item;
}

// Function to maintain records of items purchased and their subsequent stock levels
inline void maintain_purchase_details(vector<Purchase> &purchases, map<string, Item> &items) {
    Purchase purchase;
    cout << "Enter item name: ";
    cin >> purchase.item_name;
    cout << "Enter quantity: ";
    cin >> purchase.quantity;
    purchase.total_price = purchase.quantity * items[purchase.item_name].price;
    purchases.push_back(purchase);
    items[purchase.item_name].stock_level -= purchase.quantity;
}

// Function to maintain records of all facilitation fees for all sports events
inline void maintain_facilitation_fee_details(vector<FacilitationFee> &facilitation_fees, vector<Sport> &sports) {
	FacilitationFee facilitation_fee;
	cout << "Enter sport name: ";
	cin >> facilitation_fee.sport_name;

	// Iterate over the sports vector and find the sport with the matching name
	for (const Sport& sport : sports) {
	if (sport.name == facilitation_fee.sport_name) {
	    facilitation_fee.fee = sport.facilitation_fee;
	    facilitation_fees.push_back(facilitation_fee);
	    return; // Exit the loop once the matching sport is found
}
    }

    // If no matching sport is found, display an error message
    cout << "Error: Sport \"" << facilitation_fee.sport_name << "\" not found." << endl;
}

// Function to maintain records of patron's commission
inline void maintain_patron_commission_details(vector<PatronCommission> &patron_commissions, vector<Sport> &sports) {

    PatronCommission patron_commission;
    cout << "Enter sport name: ";
    cin >> patron_commission.sport_name;

    // Find the sport object that matches patron_commission.sport_name
    Sport* sport_ptr = nullptr;
    for (auto& sport : sports) {
        if (sport.name == patron_commission.sport_name) {
            sport_ptr = &sport;
            break;
        }
    }

    // If no matching sport is found, display an error message and return
    if (!sport_ptr) {
        cout << "Error: Sport \"" << patron_commission.sport_name << "\" not found." << endl;
        return;
    }

    // Calculate the commission and total commission based on the matching sport object
    patron_commission.commission = 0.2 * sport_ptr->facilitation_fee;
    patron_commission.total_commission = patron_commission.commission * sport_ptr->team_members.size();

    // Add the patron commission object to the vector
    patron_commissions.push_back(patron_commission);
}






// Function to maintain records of surcharge for lost or damaged equipment
inline void maintain_surcharge_details(vector<Surcharge> &surcharges, map<string, Item> &items) {
    Surcharge surcharge;
    cout << "Enter item name: ";
    cin >> surcharge.item_name;  
    surcharge.market_value = items[surcharge.item_name].price;
    surcharge.fee = 0.1 * surcharge.market_value;
    surcharge.total_fee = surcharge.fee * items[surcharge.item_name].stock_level;
    surcharges.push_back(surcharge);
}

// Function to compute total membership fee
inline int compute_total_membership_fee(vector<Member> &members) {
    int total_membership_fee = 0;
    for (int i = 0; i < members.size(); i++) {
        if (members[i].school_or_college == "") {
            total_membership_fee += 1000;
        } else {
            total_membership_fee += 500;
        }
    }
    return total_membership_fee;
}

// Function to compute discounted prices
inline int compute_discounted_price(vector<Purchase> &purchases) {
    int total_price = 0;
    for (int i = 0; i < purchases.size(); i++) {
        total_price += purchases[i].total_price;
    }
    int discounted_price = 0;
    if (total_price > 10000) {
        discounted_price = 0.95 * total_price;
    } else {
        discounted_price = total_price;
    }
    return discounted_price;
}

// Function to compute total amount of items bought
inline int compute_total_amount_of_items_bought(vector<Purchase> &purchases) {
    int total_amount_of_items_bought = 0;
    for (int i = 0; i < purchases.size(); i++) {
        total_amount_of_items_bought += purchases[i].quantity;
    }
    return total_amount_of_items_bought;
}

// Function to compute surcharged fee for lost or damaged equipment
inline int compute_surcharged_fee(vector<Surcharge> &surcharges) {
    int surcharged_fee = 0;
    for (int i = 0; i < surcharges.size(); i++) {
        surcharged_fee += surcharges[i].total_fee;
    }
    return surcharged_fee;
}

// Function to compute facilitation fee
inline int compute_facilitation_fee(vector<FacilitationFee> &facilitation_fees) {
    int facilitation_fee = 0;
    for (int i = 0; i < facilitation_fees.size(); i++) {
        facilitation_fee += facilitation_fees[i].total_fee;
    }
    return facilitation_fee;
}

// Function to compute patron's commission
inline int compute_patron_commission(vector<PatronCommission> &patron_commissions) {
    int patron_commission = 0;
    for (int i = 0; i < patron_commissions.size(); i++) {
        patron_commission += patron_commissions[i].total_commission;
    }
    return patron_commission;
}

// Function to compute total income for the club
inline int compute_total_income(TotalIncome &total_income) {
    total_income.total_income = total_income.membership_fee + total_income.discounted_price + total_income.total_amount_of_items_bought + total_income.surcharged_fee + total_income.facilitation_fee + total_income.patron_commission;
    return total_income.total_income;
}

// Function to generate reports
inline void generate_reports(TotalIncome &total_income) {
    cout << "Total membership fee: " << total_income.membership_fee << endl;
    cout << "Discounted price: " << total_income.discounted_price << endl;
    cout << "Total amount of items bought: " << total_income.total_amount_of_items_bought << endl;
    cout << "Surcharged fee for lost or damaged equipment: " << total_income.surcharged_fee << endl;
    cout << "Facilitation fee: " << total_income.facilitation_fee << endl;
    cout << "Patron's commission: " << total_income.patron_commission << endl;
    cout << "Total income for the club: " << total_income.total_income << endl;
}
