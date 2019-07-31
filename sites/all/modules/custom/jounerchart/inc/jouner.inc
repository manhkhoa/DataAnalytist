<?php

function get_journals_chart($form,&$form_state){
	global $base_url;

	// If file is not exists, we will generate new json file
	if(!file_exists(getcwd().'/sites/all/modules/custom/jounerchart/data/journals_db.json')){
		journal_getdata(); // Generate data
	} 

	$form['#attached']['js'] = array(
	  drupal_get_path('module', 'jounerchart') . '/js/journal.js',	  
	);

	$form['jouners-chart'] = array(
		'#markup' => '
		<div class="journal-chart">

		<style type="text/css">
			body .journal-chart{font-family: Arial, sans-serif;font-size:14px;}
			.axis path,.axis line {fill: none;stroke:#b6b6b6;shape-rendering: crispEdges;}
			/*.tick line{fill:none;stroke:none;}*/
			.tick text{fill:#999;}
			g.journal.active{cursor:pointer;}
			text.label{font-size:12px;font-weight:bold;cursor:pointer;}
			text.value{font-size:12px;font-weight:bold;}
		</style>

		<script type="text/javascript">
		function truncate(str, maxLength, suffix) {
			if(str.length > maxLength) {
				str = str.substring(0, maxLength + 1); 
				str = str.substring(0, Math.min(str.length, str.lastIndexOf(" ")));
				str = str + suffix;
			}
			return str;
		}

		var margin = {top: 20, right: 200, bottom: 0, left: 20},
			width = 800,
			height = 220;

		var start_year = 2000, 
			end_year = 2014;

		var c = d3.scale.category20c();

		var x = d3.scale.linear()
			.range([0, width]);

		var xAxis = d3.svg.axis()
			.scale(x)
			.orient("top");

		var formatYears = d3.format("0000");
		xAxis.tickFormat(formatYears);

		var svg = d3.select("body #page-wrapper #page #content .region-content .journal-chart").append("svg")
			.attr("width", width + margin.left + margin.right)
			.attr("height", height + margin.top + margin.bottom)
			.style("margin-left", margin.left + "px")
			.append("g")
			.attr("transform", "translate(" + margin.left + "," + margin.top + ")");


		d3.json("'.$base_url.'/sites/all/modules/custom/jounerchart/data/journals_db.json", function(data) {
			x.domain([start_year, end_year]);
			var xScale = d3.scale.linear()
				.domain([start_year, end_year])
				.range([0, width]);

			svg.append("g")
				.attr("class", "x axis")
				.attr("transform", "translate(0," + 0 + ")")
				.call(xAxis);

			for (var j = 0; j < data.length; j++) {
				var g = svg.append("g").attr("class","journal");

				var circles = g.selectAll("circle")
					.data(data[j]["articles"])
					.enter()
					.append("circle");

				var text = g.selectAll("text")
					.data(data[j]["articles"])
					.enter()
					.append("text");

				var rScale = d3.scale.linear()
					.domain([0, d3.max(data[j]["articles"], function(d) { return d[1]; })])
					.range([2, 9]);

				circles
					.attr("cx", function(d, i) { return xScale(d[0]); })
					.attr("cy", j*30+20)
					.attr("r", function(d) { return rScale(d[1]); })
					.style("fill", function(d) { return c(j); });

				text
					.attr("y", j*30+25)
					.attr("x",function(d, i) { return xScale(d[0])-5; })
					.attr("class","value")
					.text(function(d){ return d[1]; })
					.style("fill", function(d) { return c(j); })
					.style("display","none");

				g.append("text")
					.attr("y", j*30+25)
					.attr("x",width+40)
					.attr("class","label")
					.text(truncate(data[j]["name"],30,"..."))
					.style("fill", function(d) { return c(j); })
					.on("mouseover", mouseover)
					.on("mouseout", mouseout);
			};

			function mouseover(p) {
				var g = d3.select(this).node().parentNode;
				d3.select(g).selectAll("circle").style("display","none");
				d3.select(g).selectAll("text.value").style("display","block");
			}

			function mouseout(p) {
				var g = d3.select(this).node().parentNode;
				d3.select(g).selectAll("circle").style("display","block");
				d3.select(g).selectAll("text.value").style("display","none");
			}
		});

		</script>

		</div>'
		);

	return $form;
}