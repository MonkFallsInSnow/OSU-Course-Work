<?php

	ini_set('display_errors', 'On');
	$mysqli = new mysqli("oniddb.cws.oregonstate.edu","lewinc-db","nk3Din5wmubZVqRf","lewinc-db");
	
	if($mysqli->connect_errno)
	{
		print "Connection error " . $mysqli->connect_errno . " " . $mysqli->connect_error;
	}
	
	print "<style>table, th, td {border: 1px solid black;} </style>";
	
	foreach($_POST['tbl'] as $t)
	{
		if(isset($t))
		{	
			if($t == 'employer') //view employer table--------------------------------------------------------------
			{
				$stmt = "select name,street,city,state,zip,phone,rating from employer";
				
				if($query = $mysqli->prepare($stmt))
				{
					if($query->execute())
					{
						if($query->bind_result($name,$street,$city,$state,$zip,$phone,$rating))
						{
							print " 
									<table>
										<caption><strong>Employer</strong></caption>
										<tr>
											<th>Name</th>
											<th>Street</th>
											<th>City</th>
											<th>State</th>
											<th>Zip</th>
											<th>Phone</th>
											<th>Rating</th>
										</tr>";
								   
							while($query->fetch())
							{
								print " <tr>
											<td>{$name}</td>
											<td>{$street}</td>
											<td>{$city}</td>
											<td>{$state}</td>
											<td>{$zip}</td>
											<td>{$phone}</td>
											<td>{$rating}</td>
										</tr>";
											
							}
							
							print "</table>";
							print "<p><a href='index.php'>Back to form</a><p>";
							
							
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
					
					$query->close();
				}
				else
				{
					print "Prepare failed: " . $mysqli->errno . " " . $mysqli->error;
				}
			}
			else if($t == 'activity') //view activity table--------------------------------------------------------------
			{
				$stmt = "select description,rating from activity";
				if($query = $mysqli->prepare($stmt))
				{
					if($query->execute())
					{
						if($query->bind_result($description,$rating))
						{
							print " 
									<table>
										<caption><strong>Activity</strong></caption>
										<tr>
											<th>Description</th>
											<th>Rating</th>
										</tr>";
								   
							while($query->fetch())
							{
								print " <tr>
											<td>{$description}</td>
											<td>{$rating}</td>
										</tr>";
											
							}
							
							print "</table>";
							print "<p><a href='index.php'>Back to form</a><p>";
							
							
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
					
					$query->close();
				}
				else
				{
					print "Prepare failed: " . $mysqli->errno . " " . $mysqli->error;
				}
				
			}
			else if($t == 'activityVenue') //view activity_venue table-----------------------------------------------------------
			{
				$stmt = "select a.description, v.name 
						  from activity a 
						  inner join activity_venue av
						  on a.id=av.activityID
						  inner join venue v
						  on av.venueID=v.id
						  order by a.description";
						  
				if($query = $mysqli->prepare($stmt))
				{
					if($query->execute())
					{
						if($query->bind_result($description,$name))
						{
							print " 
									<table>
										<caption><strong>Activity_Venue</strong></caption>
										<tr>
											<th>Activity</th>
											<th>Venue</th>
										</tr>";
								   
							while($query->fetch())
							{
								print " <tr>
											<td>{$description}</td>
											<td>{$name}</td>
										</tr>";
											
							}
							
							print "</table>";
							print "<p><a href='index.php'>Back to form</a><p>";
							
							
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
					
					$query->close();
				}
				else
				{
					print "Prepare failed: " . $mysqli->errno . " " . $mysqli->error;
				}
			}
			else if($t == 'job') //view job table-----------------------------------------------------------
			{
				$stmt = "select e.name,j.title,j.description,j.pay,j.rating
						  from employer e 
						  inner join job j
						  on e.id=j.employerID";
						  
				if($query = $mysqli->prepare($stmt))
				{
					if($query->execute())
					{
						if($query->bind_result($emp,$title,$description,$pay,$rating))
						{
							print " 
									<table>
										<caption><strong>Job</strong></caption>
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
											<td>{$emp}</td>
											<td>{$title}</td>
											<td>{$description}</td>
											<td>{$pay}</td>
											<td>{$rating}</td>
										</tr>";
											
							}
							
							print "</table>";
							print "<p><a href='index.php'>Back to form</a><p>";
							
							
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
					
					$query->close();
				}
				else
				{
					print "Prepare failed: " . $mysqli->errno . " " . $mysqli->error;
				}
			}
			else if($t == 'jobSkill') //view job_skill table-----------------------------------------------------------
			{
				$stmt = "select e.name,j.title,s.name
						  from job j 
						  inner join job_skill js
						  on j.id=js.jobID
						  inner join skill s
						  on js.skillID=s.id
						  inner join employer e
						  on j.employerID=e.id";
						  
				if($query = $mysqli->prepare($stmt))
				{
					if($query->execute())
					{
						if($query->bind_result($emp,$title,$skill))
						{
							print " 
									<table>
										<caption><strong>Job_Skill</strong></caption>
										<tr>
											<th>Employer</th>
											<th>Job</th>
											<th>Skill</th>
										</tr>";
								   
							while($query->fetch())
							{
								print " <tr>
											<td>{$emp}</td>
											<td>{$title}</td>
											<td>{$skill}</td>
										</tr>";
											
							}
							
							print "</table>";
							print "<p><a href='index.php'>Back to form</a><p>";
							
							
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
					
					$query->close();
				}
				else
				{
					print "Prepare failed: " . $mysqli->errno . " " . $mysqli->error;
				}
			}
			else if($t == 'skill') //view skill table-----------------------------------------------------------
			{
				$stmt = "select name, description, proficiency from skill";
						  
				if($query = $mysqli->prepare($stmt))
				{
					if($query->execute())
					{
						if($query->bind_result($name,$description,$proficiency))
						{
							print " 
									<table>
										<caption><strong>Skill</strong></caption>
										<tr>
											<th>Name</th>
											<th>Description</th>
											<th>Proficiency</th>
										</tr>";
								   
							while($query->fetch())
							{
								print " <tr>
											<td>{$name}</td>
											<td>{$description}</td>
											<td>{$proficiency}</td>
										</tr>";
											
							}
							
							print "</table>";
							print "<p><a href='index.php'>Back to form</a><p>";
							
							
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
					
					$query->close();
				}
				else
				{
					print "Prepare failed: " . $mysqli->errno . " " . $mysqli->error;
				}
			}
			else if($t == 'skillActivity') //view skill_activty table-----------------------------------------------------------
			{
				$stmt = "select s.name, a.description, v.name
						 from skill s 
						 inner join skill_activity sa
						 on s.id=sa.skillID
						 inner join activity a 
						 on sa.activityID=a.id
						 inner join activity_venue av 
						 on av.activityID=a.id
						 inner join venue v 
						 on av.venueID=v.id
						 order by a.description";
						  
				if($query = $mysqli->prepare($stmt))
				{
					if($query->execute())
					{
						if($query->bind_result($name,$description,$venue))
						{
							print " 
									<table>
										<caption><strong>Skill_Activity</strong></caption>
										<tr>
											<th>Skill</th>
											<th>Activity</th>
											<th>Venue</th>
										</tr>";
								   
							while($query->fetch())
							{
								print " <tr>
											<td>{$name}</td>
											<td>{$description}</td>
											<td>{$venue}</td>
										</tr>";
											
							}
							
							print "</table>";
							print "<p><a href='index.php'>Back to form</a><p>";
							
							
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
					
					$query->close();
				}
				else
				{
					print "Prepare failed: " . $mysqli->errno . " " . $mysqli->error;
				}
			}
			if($t == 'venue') //view venue table--------------------------------------------------------------
			{
				$stmt = "select name,street,city,state,zip,phone,description,rating from venue";
				
				if($query = $mysqli->prepare($stmt))
				{
					if($query->execute())
					{
						if($query->bind_result($name,$street,$city,$state,$zip,$phone,$description,$rating))
						{
							print " 
									<table>
										<caption><strong>Venue</strong></caption>
										<tr>
											<th>Name</th>
											<th>Description</th>
											<th>Street</th>
											<th>City</th>
											<th>State</th>
											<th>Zip</th>
											<th>Phone</th>
											<th>Rating</th>
										</tr>";
								   
							while($query->fetch())
							{
								print " <tr>
											<td>{$name}</td>
											<td>{$description}</td>
											<td>{$street}</td>
											<td>{$city}</td>
											<td>{$state}</td>
											<td>{$zip}</td>
											<td>{$phone}</td>
											<td>{$rating}</td>
										</tr>";
											
							}
							
							print "</table>";
							print "<p><a href='index.php'>Back to form</a><p>";
							
							
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
					
					$query->close();
				}
				else
				{
					print "Prepare failed: " . $mysqli->errno . " " . $mysqli->error;
				}
			}
		}
	}
?>