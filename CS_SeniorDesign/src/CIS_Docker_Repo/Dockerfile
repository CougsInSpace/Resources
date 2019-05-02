FROM carlyishere/stk_cis:final

ARG LDLIBRARYPATH=/home/stk11.5.0/bin:$LDLIBRARYPATH
ENV LD_LIBRARY_PATH=$LDLIBRARYPATH
ARG STKINSTALLDIR=/home/stk11.5.0
ENV STK_INSTALL_DIR=$STKINSTALLDIR
ARG STKCONFIGDIR=/home/user_info/STK11/Config
ENV STK_CONFIG_DIR=$STKCONFIGDIR
ARG JAVAHOME=/usr/lib/jvm/jdk-12.0.1
ENV JAVA_HOME=$JAVAHOME

ARG ANTHOME=/home/ANT/ANT
ENV ANT_HOME=$ANTHOME
ARG PATHH=${ANT_HOME}/bin:${JAVA_HOME}/bin:${PATH}
ENV PATH=$PATHH

ARG CLASS_PATH=.
ARG CLASS_PATH=${CLASS_PATH}:/home/stk11.5.0/bin/agi.stk.javadocs.jar
ARG CLASS_PATH=${CLASS_PATH}:/home/stk11.5.0/bin/agi.swing.jar
ARG CLASS_PATH=${CLASS_PATH}:/home/stk11.5.0/bin/agi.swt.jar
ARG CLASS_PATH=${CLASS_PATH}:/home/stk11.5.0/bin/agi.core.jar
ARG CLASS_PATH=${CLASS_PATH}:/home/stk11.5.0/bin/agi.core.swing.jar
ARG CLASS_PATH=${CLASS_PATH}:/home/stk11.5.0/bin/agi.core.swt.jar
ARG CLASS_PATH=${CLASS_PATH}:/home/stk11.5.0/bin/agi.stkutil.jar
ARG CLASS_PATH=${CLASS_PATH}:/home/stk11.5.0/bin/agi.stkx.jar
ARG CLASS_PATH=${CLASS_PATH}:/home/stk11.5.0/bin/agi.stkx.swing.jar
ARG CLASS_PATH=${CLASS_PATH}:/home/stk11.5.0/bin/agi.stkx.swt.jar
ARG CLASS_PATH=${CLASS_PATH}:/home/stk11.5.0/bin/agi.stkx.initialization.jar
ARG CLASS_PATH=${CLASS_PATH}:/home/stk11.5.0/bin/agi.stkobjects.jar
ARG CLASS_PATH=${CLASS_PATH}:/home/stk11.5.0/bin/agi.stkobjects.astrogator.jar
ARG CLASS_PATH=${CLASS_PATH}:/home/stk11.5.0/bin/agi.stkvgt.jar
ARG CLASS_PATH=${CLASS_PATH}:/home/stk11.5.0/bin/agi.stkgraphics.jar
ARG CLASS_PATH=${CLASS_PATH}:/home/stk11.5.0/bin/agi.stkengine.jar
ARG CLASS_PATH=${CLASS_PATH}:/home/stk11.5.0/bin/agi.stkengine.swing.jar
ARG CLASS_PATH=${CLASS_PATH}:/home/stk11.5.0/bin/agi.stkengine.swt.jar
ARG CLASS_PATH=${CLASS_PATH}:/home/stk11.5.0/bin/agi.stk.ui.jar
ARG CLASS_PATH=${CLASS_PATH}:/home/stk11.5.0/bin/agi.stk.ui.core.jar
ARG CLASS_PATH=${CLASS_PATH}:/home/stk11.5.0/bin/agi.stk.ui.application.jar
ARG CLASS_PATH=${CLASS_PATH}:/home/stk11.5.0/bin/agi.stk.attr.jar
ARG CLASS_PATH=${CLASS_PATH}:/home/stk11.5.0/bin/agi.stk.plugin.util.jar
ARG CLASS_PATH=${CLASS_PATH}:/home/stk11.5.0/bin/agi.stk.plugin.stk.jar
ARG CLASS_PATH=${CLASS_PATH}:/home/stk11.5.0/bin/agi.stk.plugin.crdn.jar
ARG CLASS_PATH=${CLASS_PATH}:/home/stk11.5.0/bin/agi.stk.plugin.accessconstraints.jar
ARG CLASS_PATH=${CLASS_PATH}:/home/stk11.5.0/bin/agi.stk.plugin.astrogator.plugin.jar
ARG CLASS_PATH=${CLASS_PATH}:/home/stk11.5.0/bin/agi.stk.plugin.graphics.jar
ARG CLASS_PATH=${CLASS_PATH}:/home/stk11.5.0/bin/agi.stk.plugin.jar
ARG CLASS_PATH=${CLASS_PATH}:/home/stk11.5.0/bin/agi.ntvapp.jar
ARG CLASS_PATH=${CLASS_PATH}:/home/stk11.5.0/bin/agi.ntvapp.swing.jar
ARG CLASS_PATH=${CLASS_PATH}:/home/stk11.5.0/bin/agi.stk.core.jar
ARG CLASS_PATH=${CLASS_PATH}:/home/stk11.5.0/bin/agi.stk.core.swing.jar
ENV CLASSPATH=$CLASS_PATH

WORKDIR /home/OrbitalSimulationSuite/NoGraphics
RUN ls
RUN ant run >> txt.txt
RUN cat txt.txt
