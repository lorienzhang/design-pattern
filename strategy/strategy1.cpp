enum TaxBase 
{
    CN_Tax,
    US_Tax,
    DE_Tax
};

class SalesOrder
{
    TaxBase tax;

public:
    double calcTax() {
        if (tax == CN_Tax) {
            // CN****************
        } else if (tax == US_Tax) {
            // US****************
        } else if (tax == DE_Tax) {
            // DE****************
        }

        // ........
    }
};