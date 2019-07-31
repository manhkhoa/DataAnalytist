<?php

function get_bubble_chart($form,&$form_state){
	$form = array();

	drupal_add_js(drupal_get_path('module', 'bublechart').'/js/d3.min.js',array('weight' => 1));
	drupal_add_js(drupal_get_path('module', 'bublechart').'/js/jquery-1.7.2.js',array('weight' => 2));
	$form['bubble_chart'] = array(
		'#markup' => '
		<div id="table-chart" style="float: left;width: 103.2%;border: 1px solid #bbb;">
			<div id="bub-chart" style="width:72%;float:left;padding-left:200px;"></div>
		</div>
			<script>

			var diameter = 460,
			    format = d3.format(",d"),
			    color = d3.scale.category20c();

			var bubble = d3.layout.pack()
			    .sort(null)
			    .size([diameter, diameter])
			    .padding(1.5);

			var svg = d3.select("#bub-chart").append("svg")
			    .attr("width", 960)
			    .attr("height", diameter)
			    .attr("class", "bubble");

			d3.json("/json-bubble", function(error, root) {
			  var node = svg.selectAll(".node")
			      .data(bubble.nodes(classes(root))
			      .filter(function(d) { return !d.children; }))
			    .enter().append("g")
			      .attr("class", "node")
			      .attr("transform", function(d) { return "translate(" + d.x + "," + d.y + ")"; });

			  node.append("title")
			      .text(function(d) { return d.className + ": " + format(d.value); });

			  node.append("circle")
			      .attr("r", function(d) { return d.r; })
			      .style("fill", function(d) { return color(d.packageName); });

			  node.append("text")
			      .attr("dy", ".3em")
			      .style("text-anchor", "middle")
			      .text(function(d) { return d.className.substring(0, d.r / 3); });
			});

			// Returns a flattened hierarchy containing all leaf nodes under the root.
			function classes(root) {
			  var classes = [];

			  function recurse(name, node) {
			    if (node.children) node.children.forEach(function(child) { recurse(node.name, child); });
			    else classes.push({packageName: name, className: node.name, value: node.size});
			  }

			  recurse(null, root);
			  return {children: classes};
			}

			d3.select(self.frameElement).style("height", diameter + "px");

			</script>
		',
	);
	return $form;
}