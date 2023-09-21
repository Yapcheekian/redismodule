FROM redis:6

RUN apt-get update -y && apt-get install -y build-essential
COPY . /tmp
RUN cd /tmp/rmutil && make && cd ../example && make

CMD ["redis-server", "--loadmodule", "/tmp/example/module.so"]
