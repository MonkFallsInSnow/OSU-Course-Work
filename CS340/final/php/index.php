<!DOCTYPE html PUBLIC>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Survey Tool</title>
	<?php include 'script.php';?>
	
	<!-- Latest compiled and minified CSS -->
	<link rel="stylesheet" href="http://maxcdn.bootstrapcdn.com/bootstrap/3.3.6/css/bootstrap.min.css">
	
	<!-- jQuery library -->
	<script src="https://ajax.googleapis.com/ajax/libs/jquery/1.12.4/jquery.min.js"></script>

	<!-- Latest compiled JavaScript -->
	<script src="http://maxcdn.bootstrapcdn.com/bootstrap/3.3.6/js/bootstrap.min.js"></script>
</head>
<body style="background-color: rgba(200,200,200,0.1);">
	<div class="container">
		<h1>North Carolina Survey Tool</h1>
		<!-- The code used to create the tabs on this page was  inspired by http://www.w3schools.com/bootstrap/bootstrap_tabs_pills.asp See the section on Toggleable / Dynamic Tabs !-->
		<ul class="nav nav-tabs">
			<li class="active"><a data-toggle="tab" href="#insertTab">Insert Record</a></li>
			<li><a data-toggle="tab" href="#modifyTab">Modify Record</a></li>
			<li><a data-toggle="tab" href="#searchTab">Search Database</a></li>
			<li><a data-toggle="tab" href="#viewTab">View Database</a></li>
		</ul>
		
		<div class="tab-content">
			
			<!-- Insert Tab !-->
			<div id="insertTab" class="tab-pane fade in active">
				<div class="row">
					<p>
						<div class="col-lg-1"><a href="#employer">Employer</a></div>
						<div class="col-lg-1"><a href="#job">Job</a></div>
						<div class="col-lg-1"><a href="#skill">Skill</a></div>
						<div class="col-lg-1"><a href="#activity">Activity</a></div>
						<div class="col-lg-1"><a href="#venue">Venue</a></div>
					</p>
				</div>
				<!-- Add Employer Record !--------------------------------------------------------------------------->
				<br>
				<form method="post" action="addEmployer.php">
					<fieldset>
						<legend id="employer">Add Employer</a></legend>
						<div class="row">
							<div class="col-lg-2"><p>Name<input type="text" name="empName" value="" required></p></div>
						</div>
						<div class="row">
							<div class="col-lg-2"><p>Street<input type="text" name="empStreet" value=""></p></div>
						</div>
						<div class="row">
							<div class="col-lg-2"><p>City<input type="text" name="empCity" value=""></p></div>
						</div>
						<div class="row">
							<div class="col-lg-2"><p>Zip<input type="text" name="empZip" value=""></p></div>
						</div>
						<div class="row">
							<div class="col-lg-2"><p>Phone Number<input type="text" name="empPhone" value=""></p></div>
						</div>
						<div class="row">
							<div class="col-lg-1">
								<p>Rating
									<select name="empRating" required>
										<option value="">Select One</option>
										<?php showRatings();?>
									</select>
								</p>
							</div>
						</div>
						<br>
						<p><input type="submit" id="addEmployerBtn"></p>
					</fieldset>
				</form>
				
				<!-- Add Job Record !------------------------------------------------------------------------------>
				<br>
				<form method="post" action="addJob.php">
					<fieldset>
						<legend id="job">Add Job</a></legend>
						<div class="row">
							<div class="col-lg-2"><p>Title <input type="text" name="jobTitle" value="" required></p></div>
						</div>
						<div class="row">
							<div class="col-lg-2">
								<p>Employer 
								<select name="jobEmployer" required>
									<option value="">Select One</option>
									<?php $tbl = "employer"; selectName($tbl);?>
								</select>
								</p>
							</div>
						</div>
						<div class="row">
							<div class="col-lg-2"><p>Description: <input type="text" name="jobDesc" value="" required></p></div>
						</div>
						<div class="row">
							<div class="col-lg-1">
								<p>Skills
									<select name="jobSkills[]" multiple required>
										<?php $tbl = "skill"; selectName($tbl);?>
									</select>
								</p>
							</div>
						</div>
						<div class="row">
							<div class="col-lg-2"><p>Pay<input type="text" name="jobPay" value=""></p></div>
						</div>
						<div class="row">
							<div class="col-lg-1">
								<p>Rating
									<select name="jobRating" required>
										<option value="">Select One</option>
										<?php showRatings();?>
									</select>
								</p>
							</div>
						</div>
						<br>
						<p><input type="submit" id="addJobBtn"></p>
					</fieldset>
				</form>
				
				<!-- Add Skill Record !--------------------------------------------------------------------------->
				<br>
				<form method="post" action="addSkill.php">
					<fieldset>
						<legend id="skill">Add Skill</a></legend>
						<div class="row">
							<div class="col-lg-2"><p>Name<input type="text" name="skillName" value="" required></p></div>
						</div>
						<div class="row">
							<div class="col-lg-2"><p>Description<input type="text" name="skillDesc" value="" required></p></div>
						</div>
						<div class="row">
							<div class="col-lg-2">
								<p>Proficiency
									<select name="skillProf" required>
										<option value="">Select One</option>
										<?php showProficiencies();?>
									</select>
								</p>
							</div>
						</div>
						<br>
						<p><input type="submit" id="addSkillBtn"></p>
					</fieldset>
				</form>
				
				<!-- Add Activity Record !------------------------------------------------------------------->
				<br>
				<form method="post" action="addActivity.php">
					<fieldset>
						<legend id="activity">Add Activity</a></legend>
						<div class="row">
							<div class="col-lg-2"><p>Description: <input type="text" name="actDesc" value="" required></p></div>
						</div>
						<div class="row">
							<div class="col-lg-2">
								<p>Venue
									<select name="actVenues[]" multiple required>
										<?php $tbl = "venue"; selectName($tbl);?>
									</select>
								</p>
							</div>
						</div>
						<div class="row">
							<div class="col-lg-1">
								<p>Skills
									<select name="actSkills[]" multiple>
										<?php $tbl = "skill"; selectName($tbl);?>
									</select>
								</p>
							</div>
						</div>
						<div class="row">
							<div class="col-lg-1">
								<p>Rating
									<select name="actRating" required>
										<option value="">Select One</option>
										<?php showRatings();?>
									</select>
								</p>
							</div>
						</div>
						<br>
						<p><input type="submit" id="addActivityBtn"></p>
						<br>
					</fieldset>
				</form>
				
				<!-- Add Venue Record !------------------------------------------------------------------->
				<br>
				<form method="post" action="addVenue.php">
					<fieldset>
						<legend id="venue">Add Venue</a></legend>
						<div class="row">
							<div class="col-lg-2"><p>Name: <input type="text" name="venueName" type="" required></p></div>
						</div>
						<div class="row">
							<div class="col-lg-2"><p>Description: <input type="text" name="venueDesc" type="" required></p></div>
						</div>
						<div class="row">
							<div class="col-lg-2"><p>Street: <input type="text" name="venueStreet" type=""></p></div>
						</div>
						<div class="row">
							<div class="col-lg-2"><p>City: <input type="text" name="venueCity" type=""></p></div>
						</div>
						<div class="row">
							<div class="col-lg-2"><p>Zip: <input type="text" name="venueZip" type=""></p></div>
						</div>
						<div class="row">
							<div class="col-lg-2"><p>Phone Number: <input type="text" name="venuePhone" type=""></p></div>
						</div>
						<div class="row">
							<div class="col-lg-1">
								<p>Rating:
									<select name="venueRating" required>
										<option value="">Select One</option>
										<?php showRatings();?>
									</select>
								</p>
							</div>
						</div>
						<br>
						<p><input type="submit" id="addVenueBtn"></p>
					</fieldset>
				</form>
			</div>
			<!-- End Insert Tab !-->
			
			<!-- Modify Tab !-->
			<div id="modifyTab" class="tab-pane fade">
				<br>
					<fieldset>
						<legend>Jobs</legend>
							<div class="row">
								<div class="col-lg-2" style="padding-left:45px;"><h4>Employer</h4></div>
								<div class="col-lg-2" style="padding-left:50px;"><h4>Title</h4></div>
								<div class="col-lg-2" style="padding-left:65px;"><h4>Description</h4></div>
								<div class="col-lg-2" style="padding-left:130px;"><h4>Pay</h4></div>
								<div class="col-lg-2" style="padding-left:100px;"><h4>Rating</h4></div>
							</div>
					</fieldset>
				</table>
				<?php buildJobTable(); ?>
			</div>
			<!-- End Modify Tab !-->
			
			<!-- Search Tab !-->
			<div id="searchTab" class="tab-pane fade">
				<br>
				<form method="post" action="searchJob.php">
					<fieldset>
						<legend>Find Jobs</legend>
						<div class="row">
							<div class="col-lg-2">
								<p>Employer
									<select name="searchEmp">
										<option value="">Select One</option>
										<?php $tbl = 'employer'; selectName($tbl); ?>
									</select>
								</p>
							</div>
						</div>
						<div class="row">
							<div class="col-lg-2"><p>Title<input type="text" name="searchTitle" value=""></p></div>
						</div>
						<div class="row">
							<div class="col-lg-1">
								<p>Pay
									<select name="relPay">
										<option value="=">equal to</option>
										<option value=">">greater than</option>
										<option value="<">less than</option>
									</select>
									<input type="number" name="searchPay" value="">
								</p>
							</div>
						</div>
						<div class="row">
							<div class="col-lg-1">
								<p>Rating: 
									<select name="relRating">
										<option value="=">equal to</option>
										<option value=">">greater than</option>
										<option value="<">less than</option>
									</select>
									<select name="searchRating">
										<option value="">Select One</option>
										<?php showRatings(); ?>
									</select>
								</p>
							</div>
						</div>
						<br>
						<p><input type="submit" name="searchBtn" value="Search"></p>
						
					</fieldset>
				</form>
			</div>
			<!-- End Search Tab !-->
			<div id="viewTab" class="tab-pane fade">
				<br>
				<form method="post" action="viewTables.php">
					<fieldset>
						<legend>View Tables</legend>
							<div class="row">
								<div class="col-lg-4"><input type="checkbox" name="tbl[]" value="employer">Employers</div>
								<div class="col-lg-4"><input type="checkbox" name="tbl[]" value="job">Jobs</div>
								<div class="col-lg-4"><input type="checkbox" name="tbl[]" value="skill">Skills</div>
							</div>
							<br>
							<div class="row">
								<div class="col-lg-4"><input type="checkbox" name="tbl[]" value="jobSkill">Jobs & Skills</div>
								<div class="col-lg-4"><input type="checkbox" name="tbl[]" value="activity">Activities</div>
								<div class="col-lg-4"><input type="checkbox" name="tbl[]" value="venue">Venues</div>
							</div>
							<br>
							<div class="row">
								<div class="col-lg-4"><input type="checkbox" name="tbl[]" value="activityVenue">Venues & Activities</div>
								<div class="col-lg-4"><input type="checkbox" name="tbl[]" value="skillActivity">Activities & Skills</div>
							</div>
							<br>
							<input type="submit" name="viewBtn" value="Submit">
					</fieldset>
				</form>
			</div>
			<!-- View Tab !-->
		</div>
	</div>
</body>
</html>