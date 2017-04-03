<?php
	ini_set('display_errors', 'On');
	$mysqli = new mysqli("oniddb.cws.oregonstate.edu","lewinc-db","nk3Din5wmubZVqRf","lewinc-db");
	
	if($mysqli->connect_errno)
	{
		print "Connection error " . $mysqli->connect_errno . " " . $mysqli->connect_error;
	}
	
	$stmt = "select e.name,j.title,j.description,j.pay,j.rating
			from employer e
			inner join job j
			on e.id=j.employerID ";
	
	$postCounter = 0;
	if(!empty($_POST["searchEmp"]))
	{
		$postCounter++;
		$stmt .= "where j.employerID = {$_POST['searchEmp']} ";
	}
	
	if(!empty($_POST["searchTitle"]))
	{
		if($postCounter > 0)
		{
			$stmt .= "and j.title like '%{$_POST['searchTitle']}%' ";
		}
		else
		{
			$stmt .= "where j.title like '%{$_POST['searchTitle']}%' ";
		}
		$postCounter++;
	}
	
	if(!empty($_POST["searchPay"]))
	{
		if($postCounter > 0)
		{
			$stmt .= "and j.pay {$_POST['relPay']} {$_POST['searchPay']} ";
		}
		else
		{
			$stmt .= "where j.pay {$_POST['relPay']} {$_POST['searchPay']} ";
		}
		$postCounter++;
	}

	if(!empty($_POST["searchRating"]))
	{
		if($postCounter > 0)
		{
			$stmt .= "and j.rating {$_POST['relRating']} {$_POST['searchRating']} ";
		}
		else
		{
			$stmt .= "where j.rating {$_POST['relRating']} {$_POST['searchRating']} ";
		}
		$postCounter++;
	}
	
	
	//print $stmt;
	if($query = $mysqli->prepare($stmt))
	{
		if($query->execute())
		{
			if($query->bind_result($name,$title,$desc,$pay,$rating))
			{
				print "<style>table, th, td {border: 1px solid black;} </style>";
				print "<table style='border:1px solid black;'>
						<tr>
							<th>Employer</th>
							<th>Title</th>
							<th>Description</th>
							<th>Pay</th>
							<th>Rating</th>
						</tr>";
					   
				while($query->fetch())
				{
					print " <tr>
								<td>{$name}</td>
								<td>{$title}</td>
								<td>{$desc}</td>
								<td>{$pay}</td>
								<td>{$rating}</td>
							</tr>";
								
				}
				
				print "</table>";
				print "<p><a href='index.php'>Back to form</a><p>";
				$query->close();
				
			}
			else
			{
				print "Bind failed: "  . $query->errno . " " . $query->error;
			}
		}
		else
		{
			print "Execute failed: "  . $query->errno . " " . $query->error;
		}
	}
	else
	{
		print "Prepare failed: " . $mysqli->errno . " " . $mysqli->error;
	}

?>