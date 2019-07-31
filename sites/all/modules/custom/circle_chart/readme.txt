1. Run mapReduce to group drugs

db.count_drugs.drop();

counter = function() {
  emit(this.drugname,1);
}

r = function(key,values) {

 for(var i=0, sum=0; i<values.length; i++) {
      sum += values[i];
  }
  return sum;

}

res = db.drugs.mapReduce(counter, r2, {out: {reduce : 'count_drugs'}});

2. Run mapReduce to group companies

db.count_companies.drop();

counter = function() {
  emit(this.mfr_sndr,1);
}

r = function(key,values) {

 for(var i=0, sum=0; i<values.length; i++) {
      sum += values[i];
  }
  return sum;

}

res = db.demographics.mapReduce(counter, r, {out: {reduce : 'count_companies'}});