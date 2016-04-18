## the test directory shoul dreally only contain one .cc file (the main.cc)
## so I decided to keep everything here

CC = g++
LN = g++
LIBS = -lcppunit -ldl -lpaystation
PRODUCTIONDIR = ../obj
THEOBJECTS = main.o
HEADERDIRS = ../include
OBJDIR = .
CCFLAGS = -I $(HEADERDIRS)
LNFLAGS = -L$(PRODUCTIONDIR)/paystation/
OBJS = $(addprefix $(OBJDIR)/, $(THEOBJECTS))



$(OBJDIR)/testcases: $(OBJS) $(PRODUCTIONDIR)/paystation/libpaystation.a
	$(LN) $(LNFLAGS) -o $@ $(OBJS) $(LIBS)

$(OBJDIR)/%.o : %.cc
	$(CC) $(CCFLAGS) -c -o $@ $<
	$(CC) $(CCFLAGS) -MM -MP -MT $@ $< > $(basename $@).d

.PHONY : clean
clean :
	rm -f $(OBJDIR)/*.o *~ *.d

# add the dependency info to make
-include $(addsuffix .d,$(basename $(OBJS)))
