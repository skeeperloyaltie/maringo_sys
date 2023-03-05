#include "fun.h"

int main() {
    vector<Member> members;
    vector<Sport> sports;
    map<string, Item> items;
    vector<Purchase> purchases;
    vector<FacilitationFee> facilitation_fees;
    vector<PatronCommission> patron_commissions;
    vector<Surcharge> surcharges;
    TotalIncome total_income;

    // Maintain details of the club members and their roles
    maintain_member_details(members);

    // Maintain details of the sports in the club
    maintain_sport_details(sports);

    // Maintain records of the items in the store
    maintain_item_details(items);

    // Maintain records of items purchased and their subsequent stock levels
    maintain_purchase_details(purchases, items);

    // Maintain records of all facilitation fees for all sports events
    maintain_facilitation_fee_details(facilitation_fees, sports);

    // Maintain records of patron's commission
    maintain_patron_commission_details(patron_commissions, sports);

    // Maintain records of surcharge for lost or damaged equipment
    maintain_surcharge_details(surcharges, items);

    // Compute total membership fee
    total_income.membership_fee = compute_total_membership_fee(members);

    // Compute discounted prices
    total_income.discounted_price = compute_discounted_price(purchases);

    // Compute total amount of items bought
    total_income.total_amount_of_items_bought = compute_total_amount_of_items_bought(purchases);

    // Compute surcharged fee for lost or damaged equipment
    total_income.surcharged_fee = compute_surcharged_fee(surcharges);

    // Compute facilitation fee
    total_income.facilitation_fee = compute_facilitation_fee(facilitation_fees);

    // Compute patron's commission
    total_income.patron_commission = compute_patron_commission(patron_commissions);

    // Compute total income for the club
    compute_total_income(total_income);

    // Generate reports
    generate_reports(total_income);

    return 0;
}