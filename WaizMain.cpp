#include"WaizMain.h"
#include "OrderBookEntry.h"
#include"CSVReader.h"
#include"OrderBook.h"
#include<limits>

WaizMain::WaizMain(){}

void WaizMain::init()
{
 
    int input;
    currentTime=orderBook.getEarliestTime();
    wallet.insertCurrency("BTC",10);
    
    while(true){
        printMenu();
        input=getUserOption();
        processUserOption(input);
    }

}


void WaizMain::printMenu(){
    cout<<"1: Print help"<<endl;
    cout<<"2: Print Exchange Stats"<<endl;
    cout<<"3: Make an Ask"<<endl;
    cout<<"4: Make a Bid"<<endl;
    cout<<"5: Print Wallet"<<endl;
    cout<<"6: Continue"<<endl;
    cout<<"==================="<<endl;
    cout<<"Current Time:"<<currentTime<<endl;
       
}
int WaizMain::getUserOption(){
    cout<<"Select an Option Between 1 To 6"<<endl;
    int userOption=0;
    string line;
    getline(cin,line);
    try{
    userOption=stoi(line);
    }catch(const exception&e)
    {}
    cout<<"Your Choice: "<<userOption<<endl;
    return userOption;
}
void WaizMain::printHelp(){
cout<<"Help - Make Money by analysing the market,Make bids and Offers "<<endl;
}
void WaizMain::printMarketStats(){

    for(auto const& p:orderBook.getKnownProducts())
    {
        cout<<"Products : "<<p<<endl;
        vector<OrderBookEntry>entries=orderBook.getOrders(orderBookType::ask,p,currentTime);
        cout<<"Asks Seens Are: "<<entries.size()<<endl;
        cout<<"Max Ask: "<<OrderBook::getHighPrice(entries)<<endl;
        cout<<"Min Ask: "<<OrderBook::getMinPrice(entries)<<endl;

    }
//  cout<<"Orderbook Contains:"<<orders.size()<<" :enteries"<<endl;
//  unsigned int bids = 0;
//  unsigned int asks =0;
//  for(OrderBookEntry&e : orders)
//  {
//     if(e.ordertype==orderBookType::ask)
//     {
//         asks ++;
//     }
//     if(e.ordertype==orderBookType::bid)
//     {
//         bids ++;
//     }
//  }
// cout<<"OrdersBook Asks"<<asks<<endl<<"OrderBook bids"<<bids<<endl;
}
void WaizMain::enterAsk(){
    cout<<"Make an Ask-Enter the Amount:Product,Price,Amount, eg [ETH/BTC,200,0.5]"<<endl;
    string input;
    //The purpose of the function is to clear the input buffer up to the next newline character.
    getline(cin,input);
    vector<string>tokens=CSVReader::tokenise(input,',');
    if(tokens.size()!=3)
    {
        cout<<"Bad Input "<<input<<endl;
    }else
    {
        try{
        OrderBookEntry obe = CSVReader::stringsToOBE(
            tokens[1],tokens[2],currentTime,
            tokens[0],orderBookType::ask
        );
        orderBook.insertOrder(obe);
        }catch(const exception& e)
        {
            cout<<"WaizMain::enterAsk Bad Input"<<endl;
        }
    }
    cout<<"You Typed: "<<input<<endl;
    }
void WaizMain::enterBid(){
      cout<<"Make an Bid-Enter the Amount:Product,Price,Amount, eg [ETH/BTC,200,0.5]"<<endl;
    string input;
    //The purpose of the function is to clear the input buffer up to the next newline character.
    getline(cin,input);
    vector<string>tokens=CSVReader::tokenise(input,',');
    if(tokens.size()!=3)
    {
        cout<<"Bad Input "<<input<<endl;
    }else
    {
        try{
        OrderBookEntry obe = CSVReader::stringsToOBE(
            tokens[1],tokens[2],currentTime,
            tokens[0],orderBookType::bid
        );
        orderBook.insertOrder(obe);
        }catch(const exception& e)
        {
            cout<<"WaizMain::enterBid Bad Input"<<endl;
        }
    }
    cout<<"You Typed: "<<input<<endl;
    }

void WaizMain::pritWallet(){
    cout<<"Your Wallet:"<<endl;
    cout<<wallet.toString()<<endl;
}
void WaizMain::nextTimeFrame(){
     cout<<"Going to next step"<<endl;
     vector<OrderBookEntry> sales =orderBook.matchAsksToBids("ETH/BTC",currentTime);
     cout<<"Sales: "<<sales.size()<<endl;
    for(OrderBookEntry&sale: sales)
    {
        cout<<"Sale Amount: "<<sale.price<<"amount"<<sale.amount<<endl;
    }
     currentTime=orderBook.getNextTime(currentTime);
}
void WaizMain::processUserOption(int userOption ){
    if (userOption==0) {
        cout<<"Invalid Choice ,Choose between 1 to 6"<<endl;
    }
    if (userOption==1) {
        printHelp();
    }
    if (userOption==2) {
       printMarketStats();
    }
    if (userOption==3) {
        enterAsk();
    }
    if (userOption==4) {
       enterBid();
    }
    if (userOption==5) {
        pritWallet();
    }   
    if (userOption==6) {
       nextTimeFrame();
    }
}
