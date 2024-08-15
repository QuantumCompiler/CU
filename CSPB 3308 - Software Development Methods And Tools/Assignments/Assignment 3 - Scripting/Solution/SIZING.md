## Team #: 4, Team Name: Summer-team-4 

### Mondays 7pm MT

### Planning Poker Results
* **Scrum Master:** Weston Brach
* **Members:** Weston Brach, Jasmine Duran, Tyler Hopkins, Taylor Larrechea

* **Zoom Recording:**  https://drive.google.com/file/d/1q-Ks6rth5FhhTceUe5FKdBksIeYf-cZ4/view?usp=drive_link

### Stories included:  [1, 2, 3, 4, 5, 6]

### User Story : 1
<hr>

* *As a*   user
* *I want*   to upload graphs & images
* *So that*   so that I can share them with peers.

<hr>

Effort Estimation

* **Level: 3**<br><br>

<hr>

Acceptance Criteria

* **Scenario: User Uploads An Image Or Graph**

* **Given:** 	I am a user or guest user on the platform
	
* **When:** 	I navigate to the Upload section on the page
	
* **Then:** 	then the system shows an upload interface with options to upload images or graphs.

* **When:** 	The upload is successful
	
* **And:** 	    I click the Upload button
	
* **Then:** 	the system displays the uploaded image or graph in the appropriate section.

* **Scenario: Viewing Uploaded Images Or Graphs**

* **Given:** 	an image or graph has been successfully uploaded
	
* **When:** 	another user navigates to the section containing the uploaded data
	
* **Then:** 	the system displays the uploaded image or graph without any issues

* **And:**      the system ensures the image or graph is visible and properly formatted.

* **Scenario: Handling Upload Errors**

* **Given:**    I am attempting to upload an image or graph

* **When:**     the upload process encounters an error (e.g., unsupported file format, network issue)

* **Then:**     the system shows an error message indicating the reason for the failure

* **And:**      the system provides an option to retry the upload or cancel
	
<hr><hr><br><br>


### User Story : 2
<hr>

* *As a*   administrator
* *I want*   to introduce an anti-plagiarism tool
* *So that*   no ones work gets plagiarised

<hr>

Effort Estimation

* **Level: 21**<br><br>

<hr>

Acceptance Criteria

* **Scenario: Document Submission for Plagiarism Check**

* **Given:** 	a document submitted by a student
	
* **When:** 	the UI is instructed to begin processing the document
	
* **Then:** 	the system shows a processing indicator while the document is being analyzed.

* **Scenario: Plagiarism Detection Algorithm Processing** 

* **Given:**    the system has started processing the submitted document

* **When:**     the algorithm analyzes the content for potential plagiarism

* **Then:**     the system generates a plagiarism report indicating the percentage of copied content

* **And:**      the system highlights the plagiarized sections within the document

* **Scenario: Viewing Plagiarism Report**

* **Given:**    the plagiarism analysis is complete

* **When:**     the administrator or student views the plagiarism report

* **Then:**     the system shows the detailed report with sources of plagiarized content

* **And:**      the system provides recommendations for addressing the identified issues.

* **Scenario: Handling Processing Errors**

* **Given:**    the system encounters an error during document processing

* **When:**     the error occurs

* **Then:**     the system shows an error message indicating the reason for the failure

* **And:**      the system provides options to retry the analysis or upload a different document
	
<hr><hr><br><br>


### User Story : 3
<hr>

* **As a:** user
* **I want:** data visualization on Moodle
* **So that:** I have a better understanding of my progress

---

**Effort Estimation**

* **Level:** 8

---

**Acceptance Criteria**

* **Scenario: Tracking Progress Of A Student In Moodle**

* **Given:** I am a student using Moodle

* **When:** I am seeking to better understand my progress and navigate to the progress section of the course

* **Then:** The software shows helpful/ relevant data about my progress in the form of visual graphs and charts

    <br>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
    AND all of the visual charts are accurate, clear, and formatted intuitively
    <br>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
    AND the system displays specific information when I drag the cursor over the different charts.

* **When:** I click on a specific part of the chart

* **Then:** The software expands on that part and provides more in depth information

    <br>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
    AND I am able to further examine key data points
    <br>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
    AND the software gives the option to export data into various files, including PDF and CSV.
	
<hr><hr><br><br>


### User Story : 4
<hr>

* *As a*   user
* *I want*   to compare the costs and reviews of produces
* *So that*   I purchase the best available product

<hr>

Effort Estimation

* **Level: 5**<br><br>

<hr>

Acceptance Criteria

**Scenario:** User wishes to compare product 1 with product 2

* **Given:** 	that I'm in the role of a user
	
* **When:** 	I select product 1
	
* **Then:** 	the display is updated
          <br>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
          AND extracted informantion about product 1 reviews and costs is shown on the right
          <br>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
          AND the left side is open to select product 2

* **When:** 	I select product 2
	
* **Then:** 	the display is updated
          <br>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
          AND extracted informantion about product 2 reviews and costs is shown on the left
          <br>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
          AND the information for cost lines up with the infomation for product 1 cost on the right
          <br>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
          AND the information for reviews lines up with the information for product 1 reviews on the right
	
<hr><hr><br><br>


### User Story : 5

<hr>

* *As a*   busy shopper
* *I want*   to check out just one item
* *So that*   I can get done with shopping as fast as possible

<hr>

Effort Estimation

* **Level: 5**<br><br>

<hr>

Acceptance Criteria

* **Given:** 	I am a user that would like to purchase a product
	
* **When:** 	singular item is added to cart by user and user selects the option to check out
	
* **Then:** 	checkout process checks that a singular item is chosen
                <br>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
                AND provides UI with fewest actions needed to finish secure chekout for user 
	
<hr><hr><br><br>
	
<hr><hr><br><br>

### User Story : 6

<hr>

* *As a*   unsatisfied customer
* *I want*   to cancel my order
* *So that*   I get my money back

<hr>

Effort Estimation

* **Level: 13**<br><br>

<hr>

Acceptance Criteria

* **Given:** 	an unsatisfied customer would like to cancel order
	
* **When:** 	the customer selects the option to cancel order
	
* **Then:** 	a step of processes is needed to execute sequentially so that the customer gets their money back and the company gets the product back. <br>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
                - **Scenario**: Order has not been processed yet:
                <br>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
                - Order is marked as canceled through database and sends confirmation to customer while returning money for the order.
                <br>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
                - **Scenario**: Order has been processed and is staged for shipping:
                <br>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
                - Order is marked as canceled through database and sends confirmation to customer while returning money for the order. The item allocated to that order is reallocated to another order or returned to storage.
                <br>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
                - **Scenario**: Order has been processed and shipped from warehouse:
                <br>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
                -  Order is marked as canceled through database and sends confirmation to customer while returning money for the order. Item in transit is redirected/forewarded to the nearest warehouse or back to origin.
                <br>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
                - **Scenario**: Order has been received by customer already:
                <br>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
                - Order is marked as canceled through database and sends confirmation to customer with instructions on how to return product via mail or in-person. 
	
<hr><hr><br><br>