class TaxStrategy
{
public:
    virtual double calc(const Context& context) = 0;
    virtual ~TaxStrategy(){}
};

// 中国
class CNTax : public TaxStrategy
{
public:
    virtual double calc(const Context &context) override {

    }
};

// 美国
class USTax : public TaxStrategy
{
public:
    virtual double calc(const Context &context) override {

    }
};

// 德国
class DETax : public TaxStrategy
{
public:
    virtual double calc(const Context &context) override {

    }
};

class SalesOrder
{
private:
    TaxStrategy* strategy;

public:
    SalesOrder(StrategyFactory* strategyFactory) {
        this->strategy = strategyFactory->newStrategy();
    }
    ~SalesOrder() {
        delete this->strategy;
    }

    double calcTax() {
        // ...

        Context context();
        // 多态调用
        double val = strategy->calc(context);

        //...
    }
};