1. Count report, store in a collection

counter = function() {
  emit(this.product_type,1);
}

r2 = function(key,values) {

for(var i=0, sum=0; i<values.length; i++) {
      sum += values[i];
  }

  return sum;

}

res = db.enf_report.mapReduce(counter, r2, {out: {reduce : 'count_enf_rpt'}});


