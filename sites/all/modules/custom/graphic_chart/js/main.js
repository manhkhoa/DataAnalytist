(function() {

  var formatDate = d3.time.format("%b %e, %Y"),
      formatDateKey = d3.time.format("%Y%m%d"),
      formatMonth = d3.time.format("%B %Y"),
      formatPercent = d3.format("%"),
      formatPercentChange = d3.format("+%");
      formatCurrency = function(f) { f = d3.format(f); return function(d) { return f(d).replace(/^([-+])?/, "$1$$"); }; },
      formatPrice = formatCurrency(".2f"),
      formatPriceChange = formatCurrency("+.2f");
      formatYieldNumber = d3.format(".3s"),
      formatYieldChange = d3.format("+.2s");

  var bisectDate = d3.bisector(function(d) { return d.date; }).right;

  var margin = {top: 0, right: 80, bottom: 40, left: 0},
      width = 640 - margin.left - margin.right,
      height = 240 - margin.top - margin.bottom,
      mapWidth = 325,
      mapHeight = 210,
      mapMaxDate = new Date(2012, 6, 1);

  var x0 = d3.scale.ordinal()
      .domain(d3.range(1986, 2013))
      .rangeRoundBands([0, width], .15);

  var x1 = d3.time.scale()
      .range([0, x0.rangeBand()]);

  var y = d3.scale.linear()
      .domain([0, .75])
      .range([height, 0]);

  var conditions = ["very poor", "poor"];

  var conditionAxis = d3.svg.axis()
      .scale(y)
      .orient("right")
      .tickFormat(d3.format("%"));

  var drought = d3.scale.threshold()
      .domain([2, 3, 4])
      .range(["g-division", "g-division g-moderate", "g-division g-severe", "g-division g-extreme"]);

  var path = d3.geo.path()
      .projection(d3.geo.albers()
        .scale(431)
        .origin([-96, 38])
        .translate([mapWidth / 2 + 2.5, mapHeight / 2 + 2]));

  var stack = d3.layout.stack();

  var area = d3.svg.area()
      .interpolate("step-after")
      .x(function(d) { return x1(d.x); })
      .y0(function(d) { return y(d.y0); })
      .y1(function(d) { return y(d.y0 + d.y); });

  var cropDiv = d3.selectAll(".g-crop")
      .data(data.crops, function(d) { return this.id || d.id; });

  var mapG = cropDiv.select(".g-map").insert("svg", ".g-label")
      .attr("width", mapWidth)
      .attr("height", mapHeight);

  mapG.selectAll(".g-division")
      .data(data.usClimateDivisions.features)
    .enter().append("path")
      .attr("class", "g-division")
      .attr("d", path);

  mapG.selectAll(".g-state")
      .data(data.usStates.features)
    .enter().append("path")
      .attr("class", "g-state")
      .attr("d", path);

  mapG.append("image")
      .attr("xlink:href", function(d) { return "http://graphics8.nytimes.com/packages/images/newsgraphics/2012/0820-drought-crops/map-" + d.id + ".png"; })
      .attr("width", mapWidth)
      .attr("height", mapHeight);

  cropDiv.each(function(crop) {
    var cropDiv = d3.select(this),
        dispatch = d3.dispatch("update");

    var conditionYears = d3.nest()
        .key(function(d) { return d.date.getFullYear(); })
        .entries(crop.condition);

    var conditionNow = crop.condition[crop.condition.length - 1];

    var conditionG = cropDiv.select(".g-condition").append("svg")
        .attr("width", width + margin.left + margin.right + 20)
        .attr("height", height + margin.top + margin.bottom)
        .style("left", "-20px")
      .append("g")
        .attr("transform", "translate(" + (margin.left + 20) + "," + margin.top + ")");

    conditionG.append("g")
        .attr("class", "g-y g-axis")
        .attr("transform", "translate(" + width + ",0)")
        .call(conditionAxis.tickValues([conditionNow["very poor"], conditionNow["very poor"] + conditionNow["poor"]]));

    var yearG = conditionG.selectAll(".g-year")
        .data(conditionYears)
      .enter().append("g")
        .attr("class", "g-year")
        .attr("transform", function(d) { return "translate(" + x0(d.key) + ",0)"; });

    yearG.each(function(d, i) {
      var yearG = d3.select(this),
          values = d.values,
          t0 = new Date(+values[0].date),
          t1 = d3.time.week.offset(new Date(+values[values.length - 1].date), 1),
          xx = x1.domain([t0, t1]).copy();

      var areas = stack(conditions.map(function(c) {
        return values.map(function(d) {
          return {x: d.date, y: d[c]};
        }).concat([
          {x: t1, y: 0}
        ]);
      }));

      yearG.selectAll(".g-area")
          .data(areas)
        .enter().insert("path", "*")
          .attr("class", function(d, i) { return "g-area " + conditions[i].replace(/(^|\s+)/g, "$1g-"); })
          .attr("d", area);

      yearG.append("g")
          .attr("class", "g-x g-axis")
        .append("line")
          .attr("y1", height)
          .attr("y2", height)
          .attr("x2", x0.rangeBand());

      yearG.append("rect")
          .attr("class", "g-overlay")
          .attr("width", x0.rangeBand() + 3)
          .attr("height", height)
          .on("mouseover", mouseover)
          .on("mousemove", mousemove)
          .on("mouseout", mouseout);

      yearG.append("text")
          .datum(d)
          .attr("x", x0.rangeBand() / 2)
          .attr("y", height + 6)
          .attr("dy", ".71em")
          .attr("text-anchor", "middle")
          .attr("class", "g-date")
          .style("display", d.key % 4 ? "none" : null)
          .text(d.key);

      function mouseover() {
        cropDiv.selectAll(".g-condition .g-date").style("display", "none");
        yearG.selectAll(".g-date").style("display", null);
      }

      function mousemove() {
        var d1 = crop.condition[bisectDate(crop.condition, xx.invert(d3.mouse(this)[0]), 1) - 1];
        dispatch.update(d1, i);
        yearG.selectAll(".g-date").text(formatDate(d1.date));
      }

      function mouseout() {
        reset();
        cropDiv.selectAll(".g-condition .g-date").style("display", function(d) { return d.key % 4 ? "none" : null; });
        yearG.selectAll(".g-date").text(d.key);
      }
    });

    dispatch.on("update.condition", function(d1, i) {
      var p1 = d1["poor"],
          v1 = d1["very poor"];

      cropDiv.selectAll(".g-poor").text(formatPercent(p1));
      cropDiv.selectAll(".g-very.g-poor").text(formatPercent(v1));

      if (i) {
        var t1 = d1.date,
            t0 = d3.time.year.offset(t1, -1),
            d0 = conditionYears[i - 1].values[bisectDate(conditionYears[i - 1].values, t0, 1) - 1],
            p0 = d0["poor"],
            v0 = d0["very poor"];
        cropDiv.selectAll(".g-poorchange").text(formatPercentChange(p1 - p0));
        cropDiv.selectAll(".g-verypoorchange").text(formatPercentChange(v1 - v0));
      } else {
        cropDiv.selectAll(".g-poorchange,.g-verypoorchange").text("N/A");
      }
    });

    if (crop.price) dispatch.on("update.price", function(d1) {
      var t1 = d1.date,
          t0 = d3.time.year.offset(t1, -1),
          v1 = crop.price[bisectDate(crop.price, t1, 1) - 1].price,
          v0 = t1.getFullYear() > 1986 ? crop.price[bisectDate(crop.price, t0, 1) - 1].price : NaN;
      cropDiv.selectAll(".g-price").text(formatPrice(v1));
      cropDiv.selectAll(".g-pricechange").text(isNaN(v0) ? "NA" : formatPriceChange(v1 - v0));
    });

    if (crop.yield) dispatch.on("update.yield", function(d1) {
      var t1 = d1.date,
          v1 = crop.yield[t1.getFullYear()],
          v0 = crop.yield[t1.getFullYear() - 1];
      cropDiv.selectAll(".g-yield").text(formatYieldNumber(v1));
      cropDiv.selectAll(".g-yieldchange").text(isNaN(v0) ? "NA" : formatYieldChange(v1 - v0));
    });

    dispatch.on("update.map", function(d) {
      var date = d.date > mapMaxDate ? mapMaxDate : d3.time.month.floor(d.date),
          key = formatDateKey(date);
      cropDiv.selectAll(".g-map .g-division").attr("class", function(d) { return drought(data.pdsi[d.id][key]); });
      cropDiv.selectAll(".g-map .g-date").text(formatMonth(date));
    });

    reset();

    function reset() {
      dispatch.update(conditionNow, conditionYears.length - 1);
    }
  });
})();
