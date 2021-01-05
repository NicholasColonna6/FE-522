install.packages("zoo")
install.packages("tseries")
install.packages("rstudioapi")
library(zoo)
library(tseries) 
library(rstudioapi)
setwd(dirname(rstudioapi::getActiveDocumentContext()$path))

#read ticker data in from csv as dataframe, then extract just the tickers
symbols <- read.csv(file="tickers.csv", header=TRUE, sep=",")
tickers <- symbols[,1]

#counts number of tickers used
numTickers <- length(tickers)

#start and end date of data pulled
startDate <- "2014-04-30"               
endDate <- "2019-04-30"

#create zoo object to store historical data by doing just for the first ticker
price_data <- get.hist.quote(instrument = as.character(tickers[1]), start = startDate,
                    end = endDate, quote = "AdjClose", retclass = "zoo", quiet = T)

volume_data <- get.hist.quote(instrument = as.character(tickers[1]), start = startDate,
                           end = endDate, quote = "Volume", retclass = "zoo", quiet = T)

#set column name as the ticker 
dimnames(price_data)[[2]] <- as.character(tickers[1])
dimnames(volume_data)[[2]] <- as.character(tickers[1])

#now that zoo object is created, loop through all tickers, saving historical data
for (i in 2:numTickers) {
  #Displays what number ticker its on
  cat("On company ", i, " out of ", numTickers , "\n")
  
  #try to pull price data, if error, try again. If 2 errors, skip completely
  p_data <- try(x <- get.hist.quote(instrument = as.character(tickers[i]), start = startDate,
                                    end = endDate, quote = "AdjClose", retclass = "zoo", quiet = T))
  if(class(p_data) == "try-error") {
    next
  }
  else {
    dimnames(x)[[2]] <- as.character(tickers[i])  #set column name to ticker
    #add the new stock to the database 
    price_data <- merge(price_data, x)                      
    
    #try to pull volume data, if error, try again. If 2 errors, skip completely
    v_data <- try(y <- get.hist.quote(instrument = as.character(tickers[i]), start = startDate,
                                      end = endDate, quote = "Volume", retclass = "zoo", quiet = T))
    if(class(v_data) == "try-error") {
      next
    }
    else {
      dimnames(y)[[2]] <- as.character(tickers[i])  #set column name to ticker
      #add the new stock to the database 
      volume_data <- merge(volume_data, y)                      
      
    }
  }
}

#write data to a csv file
write.zoo(price_data, file = "price_data.csv", index.name = "date")
write.zoo(volume_data, file = "volume_data.csv", index.name = "date")

