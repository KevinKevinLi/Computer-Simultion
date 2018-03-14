import java.util.LinkedList; 
import com.mesquite.csim.*;
import com.mesquite.csim.Process;
import java.lang.Math;
import java.io.File;
import java.io.InputStreamReader;  
import java.io.BufferedReader;  
import java.io.FileInputStream;
import java.io.IOException;  

public class Simulation extends Model 
{	
	public static void main(String[] args) 
	{	
		if(args.length==3)
		{
			poissontime=Double.parseDouble(args[0]);
			T=Double.parseDouble(args[1]);		
			Simulation model = new Simulation();
		    //model.enableTrace(true);
		    model.run();
		}
		else if(args.length==4)
		{
			schdule=new File(args[2]);
			traveltimes=new File(args[3]);
			iffile=true;
			
			Simulation model = new Simulation();
		    //model.enableTrace(true);
		    model.run();
		}
	}
	
	public void run() 
	{
		start(new Sim());
	}

	
	double nextarrive_time=0.0;
	int train_num=0;
	static double T;
	boolean busy=false;
	LinkedList<train> dock=new LinkedList<train>();
	static double poissontime;
	int crewnum=0;
	//file
	static boolean iffile=false;
	static File schdule;
	static File traveltimes;
	String array[]=null;
	BufferedReader br; 	//schedule.txt	
	BufferedReader tr;  //traveltimes.txt
	  	                    
	
	boolean iffirst=true;//delete time0:00 train arrive
	
	//statistics
	int trainserved=0;
	LinkedList<train> statisticlist=new LinkedList<train>();
	double busytime=0.0;
	double idletime=0.0;
	double hogtime=0.0;
	double timeinqueue=0.0;//when the train is hog out but it's its turn to get in the dock,this period of waiting crew time is in the queue
	int queuemaxnum=0;

	public class crew
	{
		private double remaintime=0.0;
		private int Number=0;
		public void setremaintime(double temp)
		{
			remaintime=temp;
		}
		public double getremaintime()
		{
			return remaintime;
		}
		public void setcrewnum(int temp)
		{
			Number=temp;
		}
		public double getcrewnum()
		{
			return Number;
		}
	}
	
	public class train
	{
		private double arrive_time=0.0;
		private int number=0;
		private boolean leave=false;
		public crew c=new crew();
		private boolean hogout=false;
		private double departuretime=0.0;
		private double hogtime=0.0;
		private double unloadtime=0.0;//could be change during each update unload time
		private double totalunloadtime=0.0;//for statistic
		private double temptime=0.0;//calculate crew remain time
		private int hogtimes=0;
		
		public double getarrivetime()
		{
			return arrive_time;
		}
		public void setarrivetime(double temp)
		{
			arrive_time=temp;
		}
		public int gettrainnum()
		{
			return number;
		}
		public void settrainnum(int temp)
		{
			number=temp;
		}
		public void setleave()
		{
			leave=true;
		}
		public boolean ifleave()
		{
			return leave;
		}
		public void printremaintime()
		{
			String temp=String.format("%.2f", clock());
			int l=temp.length()+7;
			for(int i=0;i<l;i++)
			{
				System.out.printf(" ");
			}
			System.out.println("crew "+(int)c.getcrewnum() + " with " + String.format("%.2f", c.getremaintime())+"h before hogout");
		}
		public boolean ifhogout()
		{
			return hogout;
		}
		public void sethogout(boolean temp)
		{
			hogout=temp;
		}
		public double getdeparturetime()
		{
			return departuretime;
		}
		public void setdeparturetime(double temp)
		{
			departuretime=temp;
		}
		public double gethogtime()
		{
			return hogtime;
		}
		public void sethogtime(double temp)
		{
			hogtime=temp;
		}
		public void setunloadtime(double temp)
		{
			unloadtime=temp;
		}
		public double getunloadtime()
		{
			return unloadtime;
		}
		public void settemptime(double temp)
		{
			temptime=temp;
		}
		public double gettemptime()
		{
			return temptime;
		}
		public void settotalunloadtime()
		{
			totalunloadtime=getunloadtime();
		}
		public double gettotalunloadtime()
		{
			return totalunloadtime;
		}
		public void addhogtimes()
		{
			hogtimes++;
		}
		public int gethogtimes()
		{
			return hogtimes;
		}
	}
	
	
	private class Sim extends Process 
	{		
        public Sim() 
        {
        	super("Simulation");
		}

		public void run() 
		{
    	    add(new Arrival());
    	    if(iffile==false)
    	    {
    	    	hold(T);
    	    	System.out.println("Time "+String.format("%.2f", clock())+": simulation ended");
    	    }
    	    else
    	    {
    	    	hold(75000);
    	    	System.out.println("Time "+String.format("%.2f", statisticlist.getLast().getdeparturetime())+": simulation ended");
    	    }

    		statistics();
        }
    }
	
    private class Arrival extends Process 
    {

		public Arrival() {
		    super("Arrival");
	    }

	    public void run() 
	    { 	
	    try 
		{
    		InputStreamReader reader = new InputStreamReader(new FileInputStream(schdule));	    		
            br = new BufferedReader(reader);    
            InputStreamReader reader2 = new InputStreamReader(new FileInputStream(traveltimes));	    		 
        	tr = new BufferedReader(reader2);  
		}
        catch (Exception e) 
        {  
            e.printStackTrace();  
        }
	    	while(true)
	    	{	
	    		train t=new train();
	    		double arriveinterval=0.0;
	    		train_num++;
	    		crewnum++;
	    		t.settrainnum(train_num);
	    		t.c.setcrewnum(crewnum);
	    		
	    		if(iffile==false)
	    		{			
		    		t.setarrivetime(nextarrive_time);
		    		t.settemptime(nextarrive_time);	
	    			arriveinterval= -Math.log(1.0 - rand.uniform(0.0,1.0)) * poissontime;
	    	        t.setunloadtime(rand.uniform(3.5, 4.5));
	    	        t.c.setremaintime(rand.uniform(6, 11));
	    	        t.settotalunloadtime();  
	    	        dock.addLast(t);
	    			    		  		
	    	     	System.out.println("Time "+String.format("%.2f", clock())+": train " + t.gettrainnum() + " arrive for "+String.format("%.2f",t.getunloadtime())+"h of unloading");
	    		    t.printremaintime();
	    		
	    	    	if(dock.size()-1>queuemaxnum)//max train in queue(not include the train in the dock)
	        		{
	    	    		queuemaxnum=dock.size()-1;
	        		}
	     		
	        	    if(!busy)
	    	    	{
	    	            if(!statisticlist.isEmpty())
	    	            {
	    	            	idletime+=clock()-statisticlist.getLast().getdeparturetime();
	    	            }
	    	        	busy=true;
	    	    	    add(new enterdock(t));
	    	    	}
	    	        else
	    	        {
	        	    	t.sethogout(true);
	        	    	add(new hogout(t));
	    	        }			    		
	    	    
	        	    hold(arriveinterval);
	             	if(nextarrive_time>T)
	 	            {
	 	             	break;
	 	            }
	      
	        		nextarrive_time+=arriveinterval;
	       		}
	    		else//read file
	    		{   
	    			
	    			
	    			String line = "";	
	    			
	                try {
						line = br.readLine();
					} catch (IOException e) {
						
						e.printStackTrace();
					}

	                if(line!=null)
	    			{
	                	
	    			    array=line.split(" ");
	    			    t.setarrivetime(Double.parseDouble(array[0]));
	    			    t.settemptime(Double.parseDouble(array[0]));
	    			    
	    			    arriveinterval=Double.parseDouble(array[0])-nextarrive_time;
	    			    t.setunloadtime(Double.parseDouble(array[1]));
	    			    t.c.setremaintime(Double.parseDouble(array[2]));    
	    			    
	    			    t.settotalunloadtime();  
	    			    hold(arriveinterval);
	    			}
	    			else
	    			{
	    				break;
	    			}
	    			
	    	        dock.addLast(t);
	    			    		  		
	    	     	System.out.println("Time "+String.format("%.2f", clock())+": train " + t.gettrainnum() + " arrive for "+String.format("%.2f",t.getunloadtime())+"h of unloading");
	    		    t.printremaintime();
	    		
	    	    	if(dock.size()-1>queuemaxnum)//max train in queue(not include the train in the dock)
	        		{
	    	    		queuemaxnum=dock.size()-1;
	        		}
	     		
	        	    if(!busy)
	    	    	{
	    	            if(!statisticlist.isEmpty())
	    	            {
	    	            	idletime+=clock()-statisticlist.getLast().getdeparturetime();
	    	            }
	    	        	busy=true;
	    	    	    add(new enterdock(t));
	    	    	}
	    	        else
	    	        {
	        	    	t.sethogout(true);
	        	    	add(new hogout(t));
	    	        }			 
	        	    
	        	   	 
	        	    nextarrive_time=Double.parseDouble(array[0]);
	    			}
	    		       
	    	}
	    }
    }
    
    private class enterdock extends Process 
    {
    	train temp=new train();
	    public enterdock(train t) 
	    {
		    super("enterdock");
		    temp=t;
	    }

	    public void run()
	    {    	
	    	double unloadinterval=dock.getFirst().getunloadtime();
		    if(temp.c.getremaintime()>=unloadinterval)
		    {
		    	timeinqueue+=clock()-temp.getarrivetime();
		    	System.out.println("Time "+String.format("%.2f", clock())+": train " + temp.gettrainnum() + " enterdock for " + String.format("%.2f", unloadinterval)+"h of unloading");
		    	temp.printremaintime();
		    	hold(unloadinterval);
		    	departure(temp);
		    }
		    else if(temp.c.getremaintime()<unloadinterval&&temp.c.getremaintime()>0)
		    {
		    	timeinqueue+=clock()-temp.getarrivetime();
		    	System.out.println("Time "+String.format("%.2f", clock())+": train " + temp.gettrainnum() + " enterdock for " + String.format("%.2f", unloadinterval)+"h of unloading");
		    	temp.printremaintime();
		    	dock.getFirst().setunloadtime(unloadinterval-temp.c.getremaintime());
		    }
		    else if(temp.c.getremaintime()<0)
		    {
		    	System.out.println("Time "+String.format("%.2f", clock())+": train " + temp.gettrainnum() + " crew "+(int)temp.c.getcrewnum()+" hasn't arrived yet,");
		    	String temp=String.format("%.2f", clock());
				int l=temp.length()+7;
				for(int i=0;i<l;i++)
				{
					System.out.printf(" ");
				}
		    	System.out.println("cannot enter dock (SEVER HOGGED)");
		    	
		    }
	    }
    }
    
    private class hogout extends Process 
    {
    	train temp=new train();
	    public hogout(train t) 
	    {
		    super("hogout");
		    temp=t;
	    }
	    public void run()
	    {	    	
	    		double hoginterval=temp.c.getremaintime();
	    		if(temp.gettrainnum()==dock.getFirst().gettrainnum())
	    		{
	    			add(new enterdock(temp));
	    		}
	    		else
	    		{			
	    			hold(hoginterval);		    
	 		        if(!temp.ifleave())
	 		        {    	
	 		        	temp.sethogtime(clock());
	 	                System.out.println("Time "+String.format("%.2f", clock())+": train " + temp.gettrainnum() + " crew "+ (int)temp.c.getcrewnum()+" hoggedout during servicen(SERVER HOGGED)" ); 
	 	                crewnum++;
	 	                temp.c.setcrewnum(crewnum);
	 	                add(new replacement(temp));
	                 }  
	    		}
	    }
    }
    
    private class replacement extends Process
    {
    	
    	train temp=new train();
    	public replacement(train t)
    	{
    		super("replace");
    		temp=t;
    	}
    	
    	public void run()
    	{   
    		double replacetime=0.0;
    		if(iffile==false)
    		{
    			replacetime= rand.uniform(2.5,3.5);
    		}
    		else
    		{
    			String line="";
    			try {
					line = tr.readLine();
				} catch (IOException e) {
					
					e.printStackTrace();
				}
    			replacetime=Double.parseDouble(line);
    		}
    		hold(replacetime);	
    		System.out.println("Time "+String.format("%.2f", clock())+": train " + temp.gettrainnum() + " replacement crew "+ (int)temp.c.getcrewnum()+" arrives (SEVER UNHOGGED)");
    		temp.c.setremaintime(12.0-replacetime);
    		for(int i=0;i<dock.size();i++)//set crew
    		{
    		    if(dock.get(i).gettrainnum()==temp.gettrainnum())
    		    {
    		    	dock.get(i).settemptime(clock());
    		    	dock.get(i).c.setcrewnum((int)temp.c.getcrewnum());
    		    }
    		}
    		hogtime+=clock()-temp.gethogtime();
    		temp.addhogtimes();
    		add(new hogout(temp));
    	}
    }
   
    public void departure(train temp) 
    {
    	dock.removeFirst();
    	temp.setleave();
    	System.out.println("Time "+String.format("%.2f", clock())+": train " + temp.gettrainnum() + " departure");
    	trainserved++;
    	temp.setdeparturetime(clock());
    	statisticlist.addLast(temp);
    	if(!dock.isEmpty())
    	{
        	dock.getFirst().c.setremaintime(dock.getFirst().c.getremaintime()-(clock()-dock.getFirst().gettemptime()));
    		add(new enterdock(dock.getFirst()));
    	}
    	else
    	{
    		busy=false;
    	}
    }
    
    public void statistics()
    {
    	System.out.println("\n"+"Statistics"+"\n"+"----------"+"\n"+"Total number of trains served: "+trainserved);
    	//average/max time-in-system
    	double totaltimeinsys=0.0;
    	double maxtimeinsys=0.0;
    	double Time=statisticlist.getLast().getdeparturetime();
    	int [] histogram=new int [10];//max hog 10 times
    	for(int i=0;i<10;i++)
    	{
    		histogram[i]=0;
    	}
    	for(int i=0;i<trainserved;i++)
    	{
    		double temp=statisticlist.get(i).getdeparturetime()-statisticlist.get(i).getarrivetime();
    		totaltimeinsys+=temp;
    		if(temp>maxtimeinsys)
    		{
    			maxtimeinsys=temp;
    		}
    		busytime+=statisticlist.get(i).gettotalunloadtime();

    		histogram[statisticlist.get(i).gethogtimes()]++;
    	}
    	System.out.println("Average time-in-system per train: "+totaltimeinsys/trainserved+"h");
    	System.out.println("Maximum time-in-system per train: "+maxtimeinsys+"h");
    	if(iffile==false)
    	{
    		System.out.println("Dock idle percentage: "+idletime*100/Time+"%");
    	}
    	else//add the time lost about the first train
    	{
    		idletime+=statisticlist.getFirst().getarrivetime();
    		System.out.println("Dock idle percentage: "+idletime*100/Time+"%");
    	}
    	System.out.println("Dock busy percentage: "+busytime*100/Time+"%");
    	System.out.println("Dock hogged-out percentage: "+hogtime*100/Time+"%");
    	System.out.println("Average time-in-queue over trains: "+timeinqueue/trainserved);
    	System.out.println("Maximum number of trains in queue: "+queuemaxnum);
    	System.out.println("Histogram of hogout count per train:");
    	for(int i=0;i<10;i++)
    	{
    		if(histogram[i]!=0)
    		{
    			System.out.println("["+i+"]: "+histogram[i]);
    		}
    	}
    }
   
}